<?php
// $Id$

/*
 * Examples of valid statements for a drushrc.php file. Use this file to cut down on
 * typing of options and avoid mistakes.
 *
 * Rename this file to drushrc.php and optionally copy it to one of
 * four convenient places, listed below in order of precedence:
 *
 * - Drupal site folder.
 * - Drupal installation root.
 * - User Home folder (i.e. ~/.drushrc.php).
 * - Drush installation folder.
 *
 * If a configuration file is found in any of the above locations, it
 * will be loaded and merged with other configuration files in the
 * search list.
 *
 * Alternately, copy it to any location and load it with the --config (-c) option.
 * Note that this preempts loading any other configuration files!
 */

// Specify a particular multisite.
# $options['l'] = 'http://example.com/subir';

// Specify your Drupal core base directory (useful if you use symlinks).
# $options['r'] = '/home/USER/workspace/drupal-6';

// Specify CVS for checkouts
# $options['package-handler'] = 'cvs';

// Specify CVS credentials for checkouts (requires --package-handler=cvs)
# $options['cvscredentials'] = 'name:password';

// Specify additional directories to search for *.drush.inc files
// Use POSIX path separator (':')
# $options['i'] = 'sites/default:profiles/myprofile'; 

// Enable verbose mode.
# $options['v'] = 1; 


/*
 * Customize this associative array with your own tables. This is the 
 * list of tables that are entirely omitted by the 'sql dump' and 'sql load' 
 * commands when a skip-tables-key is provided. You may add new tables to the existing array or add a new 
 * element.
 */
$options['skip-tables'] = array(
 'common' => array('accesslog', 'cache', 'cache_filter', 'cache_menu', 'cache_page', 'history', 'search_dataset', 'search_index', 'search_total', 'sessions', 'watchdog'),
);

/*
 * Customize this associative array with your own tables. This is the 
 * list of tables that whose *data* is skipped by the 'sql dump' and 'sql load' 
 * commands when a structure-tables-key is provided. You may add new tables to the existing array or add a new 
 * element.
 */
$options['structure-tables'] = array(
 'common' => array('accesslog', 'cache', 'cache_filter', 'cache_menu', 'cache_page', 'history', 'search_dataset', 'search_index', 'search_total', 'sessions', 'watchdog'),
);

// Use cvs checkouts when downloading and updating modules.
// An example of a command specific argument being set in drushrc.php
// $options['package-handler'] = 'cvs';

// Specify additional directories to search for scripts
// Use POSIX path separator (':')
# $options['script-path'] = 'sites/all/scripts:profiles/myprofile/scripts';

/**
 * Variable overrides:
 *
 * To override specific entries in the 'variable' table for this site,
 * set them here. Any configuration setting from the 'variable'
 * table can be given a new value. We use the $override global here
 * to make sure that changes from settings.php can not wipe out these
 * settings.
 *
 * Remove the leading hash signs to enable.
 */
# $override = array(
#   'site_name' => 'My Drupal site',
#   'theme_default' => 'minnelli',
#   'anonymous' => 'Visitor',
# );

/**
 * Site aliases:
 *
 * To create aliases to remote Drupal installations, add entries
 * to the site-aliases option array here.  These settings can be
 * used in place of a site specification on the command line, and
 * may also be used in arguments to certain commands such as
 * "drush sync", "drush sql sync" and "drush sql load".
 *
 * Each entry in the 'site-aliases' array is accessed by its
 * site alias (e.g. 'stage' or 'dev').  Most alias records use
 * only a few of these keys; a simple alias record can be generated
 * using the "drush --full site alias" command.
 *
 * The following settings are stored in the site alias record:
 *
 * - 'db-url': The Drupal 6 database connection string from settings.php.
 *   For remote databases accessed via an ssh tunnel, set the port
 *   number to the tunneled port as it is accessed on the local machine.
 *   If 'db-url' is not provided, then drush will automatically look it
 *   up, either from settings.php on the local machine, or via backend invoke
 *   if the target alias specifies a remote server.
 * - 'databases': Like 'db-url', but contains the full Drupal 7 databases
 *   record.  Drush will look up the 'databases' record if it is not specified.
 * - 'remote-port': If the database is remote and 'db-url' contains
 *   a tunneled port number, put the actual database port number
 *   used on the remote machine in the 'remote-port' setting.
 * - 'uri': This should always be the same as the site's folder name
 *   in the 'sites' folder.
 * - 'remote-host': The fully-qualified domain name of the remote system
 *   hosting the Drupal instance.  The remote-host option must be
 *   omitted for local sites, as this option controls whether or not
 *   rsync parameters are for local or remote machines.
 * - 'remote-user': The username to log in as when using ssh or rsync.
 * - 'path-aliases': An array of aliases for common rsync targets.
 *   Relative aliases are always taken from the Drupal root.
 *     '!root': The Drupal root; must not be specified as a relative path.
 *     '!drush': The path to the folder where drush is stored.  Optional;
 *     defaults to the folder containing the running script.  Always be sure
 *     to set '!drush' if the path to drush is different on the remote server.
 *     '!drush-script': The path to the 'drush' script (used by backend invoke);
 *     default is 'drush' on remote machines, or the full path to drush.php on
 *     the local machine.
 *     '!dump': Path to the file that "drush sql sync" should use to store sql dump file.
 *     '!files': Path to 'files' directory.
 *
 * Remove the leading hash signs to enable.
 */
#$options['site-aliases']['stage'] = array(
#    'db-url' => 'pgsql://username:password@dbhost.com:port/databasename',
#    'uri' => 'stage.mydrupalsite.com',
#    'remote-host' => 'mystagingserver.myisp.com',
#    'remote-user' => 'publisher',
#    'path-aliases' => array(
#      '!root' => '/path/to/remote/drupal/root',
#      '!drush' => '/drush/path/drush',
#      '!dump' => '/path/to/live/sql_dump.sql',
#      '!files' => 'sites/mydrupalsite.com/files',
#      '!custom' => '/my/custom/path',    )
#  );
#$options['site-aliases']['dev'] = array(
#    'uri' => 'dev.mydrupalsite.com',
#    'path-aliases' => array(
#      '!root' => '/path/to/drupal/root', )
#  );

