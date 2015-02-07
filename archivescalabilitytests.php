<?php

if (count($argv) < 4) {
  print "Sorry, I don't understand the parameters you have provided.\n";
  exit();
}

/**
 * Define some global variables.
 */
$type = $argv[1];
$input_dir = $argv[2];
$output_file = $argv[3];
$log_file = 'archivescalabilitytests_log.txt';

require 'utilities.inc';

/**
 * Main script logic.
 */
register_shutdown_function('shutdown');

switch ($type) {
  case 'ZipArchive':
    require 'ZipArchive.inc';
    create_archive_zip($input_dir, $output_file);
    break;
  case 'Archive_Tar':
    create_archive_zip($input_dir, $output_file);
    break;
  default:
    "Sorry, I don't recognize that type of archive\n";
    exit();
}

