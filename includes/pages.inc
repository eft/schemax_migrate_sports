<?php

/*
 * @file
 * Migration for pages
 */

class SchemaxMigrationSportsPages extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/pages.csv';

    $this->description = t('Import pages into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'pgid' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Page ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode('page');

    $this->addFieldMapping(NULL, 'pgid');
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('field_summary', 'summary');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('body:format')
        ->defaultValue('schemax_filtered_html');

    // Add mapping for images linked to the node
    //
    // Define where the incoming images are stored
    $source_images_path = drupal_get_path('module', 'schemax_migrate_sports') . '/images';

    // Map the name of the incoming file destination field
    $this->addFieldMapping('field_image', 'imagename');
    // Make sure the source location is also mapped
    $this->addFieldMapping('field_image:source_dir')
      ->defaultValue($source_images_path);

    $this->addUnmigratedDestinations(array(
      'uid',
      'created',
      'changed',
      'status',
      'promote',
      'sticky',
      'revision',
      'log',
      'language',
      'tnid',
      'translate',
      'revision_uid',
      'is_new',
      'path',
      'comment',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('pgid', 'page_id');
    $columns[1] = array('title', 'title');
    $columns[2] = array('summary', 'summary');
    $columns[3] = array('body', 'body');
    $columns[4] = array('imagename', 'imagename');
    return $columns;
  }

}
