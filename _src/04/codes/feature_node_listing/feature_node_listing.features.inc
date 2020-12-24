<?php
/**
 * @file
 * feature_node_listing.features.inc
 */

/**
 * Implements hook_views_api().
 */
function feature_node_listing_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}
