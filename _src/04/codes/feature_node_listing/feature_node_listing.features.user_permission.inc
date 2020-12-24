<?php
/**
 * @file
 * feature_node_listing.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function feature_node_listing_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer views
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'views',
  );

  return $permissions;
}
