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
        'class_name' => 'SchemaxMigrationSportsCertifications',
        'group_name' => 'sports',
      ),
      'TeamRoles' => array(
        'class_name' => 'SchemaxMigrationSportsTeamRoles',
        'group_name' => 'sports',
      ),
      'LocationTypes' => array(
        'class_name' => 'SchemaxMigrationSportsLocationTypes',
        'group_name' => 'sports',
      ),
      'PlayingSurfaces' => array(
        'class_name' => 'SchemaxMigrationSportsPlayingSurfaces',
        'group_name' => 'sports',
      ),
      'Locations' => array(
        'class_name' => 'SchemaxMigrationSportsLocations',
        'group_name' => 'sports',
        'dependencies' => array(
          'LocationTypes',
          'PlayingSurfaces',
        ),
      ),
      'Teams' => array(
        'class_name' => 'SchemaxMigrationSportsTeams',
        'group_name' => 'sports',
        'dependencies' => array(
          'TeamRoles',
        ),
      ),
      'Players' => array(
        'class_name' => 'SchemaxMigrationSportsPlayers',
        'group_name' => 'sports',
        'dependencies' => array(
          'Teams',
          'TeamRoles',
        ),
      ),
      'Staff' => array(
        'class_name' => 'SchemaxMigrationSportsStaff',
        'group_name' => 'sports',
        'dependencies' => array(
          'Certifications',
          'Teams',
          'TeamRoles',
        ),
      ),
      'Staff1' => array(
        'class_name' => 'SchemaxMigrationSportsStaff1',
        'group_name' => 'sports',
        'dependencies' => array(
          'Certifications',
          'Teams',
          'TeamRoles',
        ),
      ),
      'Staff2' => array(
        'class_name' => 'SchemaxMigrationSportsStaff2',
        'group_name' => 'sports',
        'dependencies' => array(
          'Certifications',
          'Teams',
          'TeamRoles',
          'Staff1',
        ),
      ),
      'Practices' => array(
        'class_name' => 'SchemaxMigrationSportsPractices',
        'group_name' => 'sports',
        'dependencies' => array(
          'Teams',
          'TeamRoles',
        ),
      ),
      'Pages' => array(
        'class_name' => 'SchemaxMigrationSportsPages',
        'group_name' => 'content',
      ),
      'FPPs' => array(
        'class_name' => 'SchemaxMigrationSportsFPPs',
        'group_name' => 'content',
      ),
      'MenuLinks' => array(
        'class_name' => 'SchemaxMigrationSportsMenuLinks',
        'group_name' => 'content',
      ),
      'Images' => array(
        'class_name' => 'SchemaxMigrationSportsImages',
        'group_name' => 'sports',
      ),
      'TestTeams' => array(
        'class_name' => 'SchemaxMigrationSportsTestTeams',
        'group_name' => 'test',
      ),
      'TestPersons' => array(
        'class_name' => 'SchemaxMigrationSportsTestPersons',
        'group_name' => 'test',
        'dependencies' => array(
          'TestTeams',
        ),
      ),
      'TestPlayers' => array(
        'class_name' => 'SchemaxMigrationSportsTestPlayers',
        'group_name' => 'test',
        'dependencies' => array(
          'TestTeams',
        ),
      ),
      'TestStaff1' => array(
        'class_name' => 'SchemaxMigrationSportsTestStaff1',
        'group_name' => 'test',
        'dependencies' => array(
          'Certifications',
          'TestTeams',
          'TeamRoles',
        ),
      ),
      'TestStaff2' => array(
        'class_name' => 'SchemaxMigrationSportsTestStaff2',
        'group_name' => 'test',
        'dependencies' => array(
          'Certifications',
          'TestTeams',
          'TeamRoles',
          'Staff1',
        ),
      ),
    ),
  );

  return $api;
}
