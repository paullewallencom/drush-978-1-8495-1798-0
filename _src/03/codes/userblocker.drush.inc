<?php
/**
 * @file
 * Blocks users with no activity in a period of time
 */

/**
 * Implementation of hook_drush_command().
 */
function userblocker_drush_command() {
  $items['user-blocker'] = array(
    'description' => 'Blocks user accounts with no activity in a period of time.',
    'aliases' => array('ub'),
    'examples' => array(
      'drush user-blocker' => 'Blocks user accounts who did not log in in the last two years.',
      'drush user-blocker en es' => 
        'Blocks user accounts who did not log in in the last two years and whose default language ' .
        'is English or Spanish.',
      'drush user-blocker --since="two months ago" es' => 
        'Blocks user accounts who did not log in in the last two months and whose default language ' .
        'is Spanish.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array(
      'languages' => 'A list of languages to filter user accounts.',
    ),
    'options' => array(
      'since' => 'Specifies last time a user account should have logged in so it wont get ' .
                 'blocked. Defaults to 2 years ago. Accepts all date formats ' .
                 'described at http://www.php.net/manual/en/datetime.formats.php.show.'  ,
    ),
  );
  return $items;
}

/**
 * Implementation of drush_hook_COMMAND_validate()
 */
function drush_userblocker_user_blocker_validate() {
  // Validate the language arguments if they were given
  $languages = func_get_args();
  if (count($languages)) {
    $languages = array_unique($languages);
    $valid_languages = array_intersect($languages, array_keys(language_list()));
    if (count($languages) != count($valid_languages)) {
      return drush_set_error('INVALID_LANGUAGE', dt('At least one of the languages given does not exist.'));
    }
  }
  // Validate if a valid date was given
  if (drush_get_option('since')) {
    if (!strtotime(drush_get_option('since'))) {
      return drush_set_error('INVALID_SINCE_DATE', dt('The date given at the --since option is invalid.'));
    }
  }
}

/**
 * Callback implementation for user-blocker command
 */
function drush_userblocker_user_blocker() {
  // Grab all languages given. If any.
  $languages = func_get_args();

  // See if we received a date from which we should filter
  $since = strtotime(drush_get_option('since', '2 years ago')); 

  // Perform the update over the users table
  $query= db_update('users')
  ->fields(array(
    'status' => 0,
  ))
  ->condition('uid', array(0, 1), 'NOT IN')
  ->condition('access', array(1, $since), 'BETWEEN');

  // Add the condition to filter by language
  if (count($languages)) {
    $query->condition('language', $languages, 'IN');
  } 

  $total_blocked = $query->execute();
  drush_log(dt("Blocked !total_blocked users", array('!total_blocked' => $total_blocked)), 'success');
}
