<?php

function complete_drush_command() {
  $items['complete'] = array(
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap.
  );
  return $items;
}


function drush_complete_complete() {
  // Set up arguments as if we were running the command, and attempt to parse.
  $args = drush_get_context('argv');
  // TODO: This needs work.
  // For some reason we get duplicate drush/drush.php arguments in some cases,
  // we also need to remove the "complete" command (running now).
  $args = preg_grep("/(drush|drush.php|complete)/", $args, PREG_GREP_INVERT);
  // We also get an empty argument on the end when we autocomplete on just 'drush '.
  $last_word = end($args);
  if (empty($last_word)) {
    array_pop($args);
  }
  // Add the drush command back in, since we removed it above.
  array_unshift($args, 'drush');
  // Reindex the array.
  $args = array_values($args);
  drush_set_context('argv', $args);
  drush_set_command(NULL);
  drush_parse_args();
  drush_parse_command();

  $complete = array();
  $command = drush_get_command();
  $command_name = $command['command'];
  $cache_filename = sys_get_temp_dir() . '/drush_complete.' . substr(md5(DRUPAL_ROOT . drush_get_context('DRUSH_DRUPAL_SITE_ROOT')), 0, 5);
  if (file_exists($cache_filename)) {
    $cache = file_get_contents($cache_filename);
    $complete = unserialize($cache);
  }
  if (empty($complete)) {
    // Bootstrap to the highest level possible (up to the database level).
    drush_bootstrap_max(DRUSH_BOOTSTRAP_DRUPAL_DATABASE);
    $complete = drush_command_invoke_all('drush_complete');
    foreach (array_keys(drush_get_commands()) as $command_key) {
      if (!isset($complete['commands'][$command_key])) {
        $complete['commands'][$command_key] = NULL;
      }
    }
  }
//  print_r($complete);
  $completions = array();

  // Argument debugging code
//  foreach ($args as $n => $arg) {
//    $completions[] = $n.'-'.$arg;
//  }
  
  // Add in any command specific options.
  if ($command && $command_name !== 'help') {
    $complete['options'] = array_merge($complete['options'], array_keys($command['options']));
  }
  // Remove any options that have been already specified.
  foreach (array_keys(drush_get_merged_options()) as $option) {
    unset($complete['options'][array_search('--' . $option, $complete['options'])]);
  }

  // Complete options (starting with a hypnen) first.
  $last_word = end($args);
  if ($last_word[0] == '-') {
    $completions = preg_grep("/^$last_word/", $complete['options']);
  }
  else if ($command && $command_name !== 'help') {
    // We do have a valid command already, so we try matching command arguments.
    $complete_arguments = array();
    if (isset($complete['commands'][$command_name])) {
      if (is_array($complete['commands'][$command_name])) {
        // Arguments can be added as an array on the command.
        $complete_arguments = $complete['commands'][$command_name];
      }
      if (is_string($complete['commands'][$command_name]) && isset($complete[$complete['commands'][$command_name]]) && is_array($complete[$complete['commands'][$command_name]])) {
        // Alternatively a key to retrieve argument sets shared between multiple commands.
        $complete_arguments = $complete[$complete['commands'][$command_name]];
      }
    }
    while (!empty($args) && empty($completions)) {
      $candidate = implode(' ', $args);
      $completions = preg_grep("/^$candidate/", $complete_arguments);
      array_shift($args);
    }
    if (empty($completions)) {
      $completions = array_merge($complete_arguments, $complete['options']);
    }
  }
  else {
    // We don't have a valid command, so we complete available commands trying
    // the longest match first.
    while (!empty($args) && empty($completions)) {
      $candidate = implode(' ', $args);
      $completions = preg_grep("/^$candidate/", array_keys($complete['commands']));
      array_shift($args);
    }
  }
  // The default, if we haven't yet found any context sensitive completions is
  // to return commands and options.
  if (empty($completions)) {
    $completions = array_merge(array_keys($complete['commands']), $complete['options']);
  }
  drush_print(implode("\n", $completions));
  if (!file_exists($cache_filename)) {
    file_put_contents($cache_filename, serialize($complete));
  }
}

function core_drush_complete() {
  // TODO: Store this in a better structured format upstream
  $complete = array();
  preg_match_all('/--[a-z-]*/', implode(' ', array_keys(drush_get_option_help())), $matches);
  $complete['options'] = $matches[0];

  if (drush_get_context('DRUSH_BOOTSTRAP_PHASE') >= DRUSH_BOOTSTRAP_DRUPAL_DATABASE) {
    $result = db_query('SELECT DISTINCT(type) FROM {watchdog} ORDER BY type');
    while ($object = db_fetch_object($result)) {
      $complete['watchdog'][] = $object->type;
    }
    $complete['commands']['watchdog show'] = 'watchdog';
    $complete['commands']['watchdog delete'] = 'watchdog';
  }
  return $complete;
}

