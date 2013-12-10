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
      'MigrateAddressFieldHandler',
    ),
    'groups' => array(
      'sports' => array(
        'title' => t('Sports Imports'),
      ),
      'test' => array(
        'title' => t('Test Imports'),
      ),
    ),
    'migrations' => array(
      'CertificationTerm' => array(
        'class_name' => 'SchemaxSportsMigrationCertifications',
        'group_name' => 'sports',
      ),
      'Teams' => array(
        'class_name' => 'SchemaxSportsMigrationTeams',
        'group_name' => 'sports',
      ),
      'Players' => array(
        'class_name' => 'SchemaxSportsMigrationPlayers',
        'group_name' => 'sports',
        'dependencies' => array(
          'Teams',
        ),
      ),
      'Staff' => array(
        'class_name' => 'SchemaxSportsMigrationStaff',
        'group_name' => 'sports',
        'dependencies' => array(
          'Teams',
          'CertificationTerm',
        ),
      ),
      'TestTeams' => array(
        'class_name' => 'SchemaxSportsMigrationTestTeams',
        'group_name' => 'test',
      ),
      'TestPlayers' => array(
        'class_name' => 'SchemaxSportsMigrationTestPlayers',
        'group_name' => 'test',
        'dependencies' => array(
          'TestTeams',
        ),
      ),
    ),
  );

  return $api;
}
