<?php

/*
 * @file
 * Migration for players
 */

class SchemaxSportsMigrationCertifications extends SchemaxSportsMigration {

  public function __construct($arguments) {
    parent::__construct($arguments);

    $source_file_path = drupal_get_path('module', 'schemax_migrate_sports') . '/csv/certifications.csv';

    $this->description = t('Import certifications into the database');
    $this->source = new MigrateSourceCSV($source_file_path, $this->csvcolumns(), array('header_rows' => 1), $this->fields());

    // Create a map object for tracking the relationships between source rows
    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'certification' => array('type' => 'varchar',
                           'length' => 255,
                           'not null' => TRUE,
                           'description' => 'Official Certification',
                          )
        ),
        MigrateDestinationTerm::getKeySchema()
      );

    $this->destination = new MigrateDestinationTerm('certifications');

    $this->addFieldMapping('name', 'certification');

    $this->addUnmigratedDestinations(array(
      'tid',
      'description',
      'parent',
      'parent_name',
      'format',
      'weight',
      'path',
    ));
  }

  // Define columns in source CSV file
  protected function csvcolumns() {

    $columns[0] = array('certification', 'Certification');
    return $columns;
  }

  // Define fields
  protected function fields() {
    // use empty array by default
    return array();
  }

  public function prepareRow($row) {
    // Always include this fragment at the beginning of every prepareRow()
    // implementation, so parent classes can ignore rows.
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    //$row->player_date_of_birth = $row->player_date_of_birth . '-01-02 00:00:00';

    return TRUE;
  }

}
