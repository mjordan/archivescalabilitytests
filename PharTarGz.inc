<?php

/**
 * @param string $input_dir_path
 *   The path to the directory containing the input files.
 *
 * @pararm string $output_file_basename
 *   The basename of the output .tar.gz file.
 *
 */
function create_archive_zip($input_dir_path, $output_file_basename) {
  try {
    $phar = new PharData($output_file_basename . '.tar');
  }
  catch (Exception $e) {
    write_log_entry('Create Phar Tar (gz)', __LINE__, $e->getMessage());
  }
  try {
    $phar->buildFromDirectory(dirname(__FILE__) . '/' . $input_dir_path);
  }
  catch (Exception $e) {
    write_log_entry('Create Phar Tar (gz)', __LINE__, $e->getMessage());
  }
  try {
    $phar->compress(Phar::GZ);
    unset($phar);
    $output_file_name = $output_file_basename . '.tar.gz';
    unlink($output_file_basename . '.tar');
    $stats = get_file_stats($output_file_name);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
  }
  catch (Exception $e) {
    $stats = get_file_stats($output_file_name);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
    write_log_entry('Create Phar Tar (gz)', __LINE__, $e->getMessage());
  }
}

