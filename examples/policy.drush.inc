<?php
// $Id$

/**
 * @file
 *   Example policy commandfile. Modify as desired.
 *
 *   Validates commands as they are issued and returns an error 
 *   or changes options when policy is violated.
 *
 *   You can copy this file to any of the following
 *     1. A .drush folder in your HOME folder.
 *     2. Anywhere in a folder tree below an active module on your site.
 *     3. /usr/share/drush/commands (configurable)
 *     4. In an arbitrary folder specified with the --include option.
 */

/**
 * Implement of drush_hook_COMMAND_validate().
 * 
 * Prevent catastrophic braino.
 */
function drush_policy_sql_sync_validate($source = NULL, $destination = NULL) {
  if ($destination == '@prod') {
    return drush_set_error(dt('WTF. Don\'t overwrite the production database.'));
  }
}

/**
 * Implement of drush_hook_COMMAND_validate().
 *
 * To test this example without copying, execute `drush --include=./examples updatedb`
 * from within your drush directory.
 * 
 * Unauthorized users may view pending updates but not execute them.
 */
function drush_policy_updatedb_validate() {
  // Check for a token in the request. In this case, we require --token=secret.
  if (!drush_get_option('token') == 'secret') {
    drush_set_context('DRUSH_AFFIRMATIVE', FALSE);
    drush_set_context('DRUSH_NEGATIVE', TRUE);
  }
}

/*
 * Implementation of drush_hook_COMMAND_validate().
 * 
 * Only sudo tells me to make a sandwich: http://xkcd.com/149/
 */
function drush_policy_make_me_a_sandwich_validate() {
  $name = posix_getpwuid(posix_geteuid());
  if ($name['name'] !== 'root') {
    return drush_set_error('MAKE_IT_YOUSELF', dt('What? Make your own sandwich.'));
  }
}

