<?php

/*
 * You must implement hook_migrate_api(), setting the API level to 2, for
 * your migration classes to be recognized by the Migrate module.
 */

function schemax_migrate_sports_migrate_api() {
  $api = array(
    'api' => 2,
    // Date module doesn't register handler according to new Migrate 2.6 requirements
    // that's why we register it here.
    'field handlers' => array(
      'DateMigrateFieldHandler',
    ),
    'groups' => array(
      'sports' => array(
        'title' => t('Sports Imports'),
      ),
    ),
    'migrations' => array(
      'PlayerNode' => array(
        'class_name' => 'SchemaxSportsMigrationPlayer',
        'group_name' => 'sports',
      ),
      'TeamNode' => array(
        'class_name' => 'SchemaxSportsMigrationTeam',
        'group_name' => 'sports',
      ),
      'TeamNode2' => array(
        'class_name' => 'SchemaxSportsMigrationTeam2',
        'group_name' => 'sports',
      ),
    ),
  );

  return $api;
}