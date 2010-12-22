<?php
// $Id$

/**
 * @file
 *   Drush support for nodes.
 */

/**
 * Implementation of hook_drush_command().
 */
function node_drush_command() {
  $items = array();

  $items['node-show'] = array(
    'description' => "Print node objects to stdout",
    'arguments' => array(
      'nids' => "A list of space-separated node IDs to print to stdout.",
    ),
    'options' => array(
      'json' => "Output the node as JSON",
    ),
    'examples' => array(
      'drush node-show 4' => 'Print the node object of node/4 to stdout',
    ),
    'aliases' => array('ns'),
  );
  $items['node-edit'] = array(
    'description' => "Edit a node as json in the default editor",
    'arguments' => array(
      'nids' => "A node id",
    ),
    'examples' => array(
      'drush node-edit 4' => 'Edit node 4 as json in the default editor',
    ),
    'aliases' => array('ne'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function node_drush_help($section) {
  switch ($section) {
  case 'drush:node-show':
    return dt("Print node objects to stdout");
  case 'drush:node-edit':
    return dt("Edit a node as json in the default editor");
  }
}

/**
 * Drush command callback.
 *
 * Show nodes.
 */
function drush_node_show($nids) {
  if (!is_array($nids)) $nids = array($nids);
  foreach($nids as $nid) {
    $node = node_load($nid);
    if (drush_get_option('json')) {
      drush_print(json_encode($node));
    }
    else {
      drush_print_r($node);
    }
  }
}

/**
 * Drush command callback.
 *
 * Show nodes.
 */
function drush_node_edit($nid) {
  $node = node_load($nid);
  $tmp_file = drush_save_data_to_temp_file(json_encode($node));
  drush_shell_exec_interactive('$EDITOR ' . $tmp_file);
  $edited_node = file_get_contents($tmp_file, "r");
  node_save(json_decode($edited_node));
}
