<?php
/**
 * @file
 * Site aliases for Festival website
 */

/**
 * Local site alias (http://festival.localhost)
 */
$aliases['local'] = array(
  'root' => '/home/juampy/projects/festival',
  'uri'  => 'festival.localhost',
  'path-aliases' => array(
    '%dump-dir' => '/tmp',
  ),
);

/**
 * Development site alias (http://festival.dev.drush)
 */
$aliases['dev'] = array(
  'uri' => 'festival.dev.drush',
  'root' => '/var/www/festival.dev.drush',
  'remote-user' => 'username',
  'remote-host' => 'festival.dev.drush',
  'path-aliases' => array(
    '%dump-dir' => '/tmp',
  ),
  'source-command-specific' => array(
    'sql-sync' => array(
      'no-cache' => TRUE,
      'structure-tables-key' => 'common',
    ),
  ),
  'command-specific' => array(
    'sql-sync' => array (
      'no-ordered-dump' => TRUE,
      'sanitize' => TRUE,
      'structure-tables' => array(
        'common' => array('cache', 'cache_filter', 'cache_menu', 'cache_page', 'history',
                          'sessions', 'watchdog'),
      ),
    ),
  ),
);

/**
 * Production site alias (http://festival.drush)
 */
$aliases['prod'] = array(
  'parent' => '@festival.dev',
  'uri' => 'festival.drush',
  'root' => '/var/www/festival.drush',
  'remote-user' => 'username-prod',
  'remote-host' => 'festival.drush',
);
