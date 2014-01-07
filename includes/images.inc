<?php

/*
 * @file
 * Migration for players
 */

class SchemaxMigrationSportsImages extends SchemaxMigrationSports {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/images.csv';

    $this->description = t('Import images into the database');
    $this->source = new MigrateSourceCSV($source_file_path, array(), array('header_rows' => 1), array());


    $this->destination = new MigrateDestinationFile();
    $this->map = new MigrateSQLMap($this->machineName,
        array('imageid' => array(
              'type' => 'int',
              'unsigned' => TRUE,
              'not null' => TRUE,
              'description' => 'Image ID.'
              )
           ),
        MigrateDestinationFile::getKeySchema()
    );

    $this->addFieldMapping('imageid', 'imageid');

    $source_images_path = drupal_get_path('module', 'schemax_migrate_sports') . '/images';
    $this->addFieldMapping('source_dir')
      ->defaultValue($source_images_path);

    $this->addUnmigratedDestinations(array(
      'destination_dir',
      'destination_file',
      'fid',
      'file_replace',
      'preserve_files',
      'timestamp',
      'uid',
      'urlencode',
    ));

  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('location_id', 'Location ID');
    $columns[1] = array('location', 'Location');
    $columns[2] = array('playing_surface', 'Playing Surface');
    $columns[3] = array('location_type', 'Location Type');
    $columns[4] = array('geo_type', 'GeoType');
    $columns[5] = array('wkt', 'WKT');
    $columns[6] = array('input_format', 'Input Format');
    return $columns;
  }



}
