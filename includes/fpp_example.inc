<?php

/*
 * @file
 * Migration for teams
 */

class SchemaxMigrationSportsFPPs extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/fpp.csv';
    $this->description = t('Import field panel panes into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    $this->map = new MigrateSQLMap($this->machineName, array(
      'fpid' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'FPP ID',
      ),
        ), MigrateDestinationFieldablePanelsPanes::getKeySchema()
    );

    // Create destination
    $this->destination = new MigrateDestinationFieldablePanelsPanes('schemax_base_featured_content');

    // Define field mappings
    $this->addFieldMapping(NULL, 'fpid');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('reusable', 'reusable')
        ->defaultValue(1);
    $this->addFieldMapping('admin_title', 'admin_title');
    $this->addFieldMapping('admin_description', 'admin_description');
    $this->addFieldMapping('category', 'category');

    // field_featured_content is an entity reference field pointing to one or more page nodes
    $this->addFieldMapping('field_featured_content', 'pgid')
        ->sourceMigration('Pages')
        ->separator('|')
        ->description('This is an entity reference from the Pages migration');

    $this->addUnmigratedDestinations(array(
      'vid',
      'bundle',
      'link',
      'path',
      'view_access',
      'edit_access',
      'created',
      'changed',
      'uuid',
      'language',
    ));
  }

  /**
   * Source columns array
   * @return mixed
   */
  function csvcolumns() {
    $columns[0] = array('fpid', 'FPP ID');
    $columns[1] = array('title', 'Title');
    $columns[2] = array('reusable', 'Reusable');
    $columns[3] = array('admin_title', 'Admin Title');
    $columns[4] = array('admin_description', 'Admin Description');
    $columns[5] = array('category', 'Admin Category');
    $columns[6] = array('pgid', 'Page ID');
    return $columns;
  }

}
