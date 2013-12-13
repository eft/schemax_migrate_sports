<?php

/*
 * @file
 * Migration for players
 */

class SchemaxSportsMigrationLocations extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/locations.csv';

    $this->description = t('Import locations into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), array());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName, array(
      'location_id' => array(
        'type' => 'int',
        'not null' => TRUE,
        'description' => 'Location ID',
      ),
        ), MigrateDestinationNode::getKeySchema()
    );

    $this->destination = new MigrateDestinationNode('schemax_location');

    $this->addFieldMapping(NULL, 'location_id');
    $this->addFieldMapping('title', 'location');
    $this->addFieldMapping('field_schemax_playing_surfaces', 'playing_surface');
    $this->addFieldMapping('field_schemax_location_types', 'location_type');

    $this->addFieldMapping('field_schemax_geo', 'wkt');
    // Add a source wkt (text) field
    //$this->addFieldMapping('field_schemax_geo:wkt', 'wkt');
    //$this->addFieldMapping('field_schemax_geo:input_format', 'input_format');

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
      'field_schemax_geo:lat',
      'field_schemax_geo:lon',
      'field_schemax_geo:left',
      'field_schemax_geo:top',
      'field_schemax_geo:right',
      'field_schemax_geo:bottom',
      'field_schemax_geo:geohash',
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

//    $columns[6] = array('lat', 'Lat');
//    $columns[7] = array('lon', 'Lon');
//    $columns[8] = array('left', 'Left');
//    $columns[9] = array('top', 'Top');
//    $columns[10] = array('right', 'Right');
//    $columns[11] = array('bottom', 'Bottom');
    return $columns;
  }

//  protected function transform_wkt($value) {
//
//  }
//
//  public function prepareRow($row) {
//
//    // Get the WKT string
//    $wkt_text = $row->wkt;
//    // instantiate a new geometry object from the original WKT string
//    $geom = geoPHP::load($wkt_text, 'wkt');
//    // output the geometry in binary format
//    $wkb = $geom->out('wkb');
//
//    // Store binary value in input row
//    $row->geom = $wkb;
//
//    // generate a geohash value
//    $geohash_truncated = substr($geom->out('geohash'), 0, GEOFIELD_GEOHASH_LENGTH);
//
//    // store geohash in input row
//    $row->geohash = $geohash_truncated;
//  }

}
