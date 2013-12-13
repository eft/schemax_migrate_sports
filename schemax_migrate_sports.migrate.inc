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
      'MigrateGeofieldFieldHandler',
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
      'Certifications' => array(
        'class_name' => 'SchemaxSportsMigrationCertifications',
        'group_name' => 'sports',
      ),
      'TeamRoles' => array(
        'class_name' => 'SchemaxSportsMigrationTeamRoles',
        'group_name' => 'sports',
      ),
      'LocationTypes' => array(
        'class_name' => 'SchemaxSportsMigrationLocationTypes',
        'group_name' => 'sports',
      ),
      'PlayingSurfaces' => array(
        'class_name' => 'SchemaxSportsMigrationPlayingSurfaces',
        'group_name' => 'sports',
      ),
      'Locations' => array(
        'class_name' => 'SchemaxSportsMigrationLocations',
        'group_name' => 'sports',
        'dependencies' => array(
          'LocationTypes',
          'PlayingSurfaces',
        ),
      ),
      'Teams' => array(
        'class_name' => 'SchemaxSportsMigrationTeams',
        'group_name' => 'sports',
        'dependencies' => array(
          'TeamRoles',
        ),
      ),
      'Players' => array(
        'class_name' => 'SchemaxSportsMigrationPlayers',
        'group_name' => 'sports',
        'dependencies' => array(
          'Teams',
          'TeamRoles',
        ),
      ),
      'Staff' => array(
        'class_name' => 'SchemaxSportsMigrationStaff',
        'group_name' => 'sports',
        'dependencies' => array(
          'Certifications',
          'Teams',
          'TeamRoles',
        ),
      ),
      'Practices' => array(
        'class_name' => 'SchemaxSportsMigrationPractices',
        'group_name' => 'sports',
        'dependencies' => array(
          'Teams',
          'TeamRoles',
        ),
      ),
      'TestTeams' => array(
        'class_name' => 'SchemaxSportsMigrationTestTeams',
        'group_name' => 'test',
      ),
      'TestPersons' => array(
        'class_name' => 'SchemaxSportsMigrationTestPersons',
        'group_name' => 'test',
        'dependencies' => array(
          'Teams',
        ),
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
