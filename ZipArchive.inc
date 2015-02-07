<?php

/**
 * @param string $input_dir_path
 *   The path to the directory containing the input files.
 *
 * @pararm string $output_file_path
 *   The path to the output .zip file.
 *
 */
function create_archive_zip($input_dir_path, $output_file_path) {
  $zip = new ZipArchive();
  try {
    $zip->open($output_file_path, ZIPARCHIVE::CREATE);
  }
  catch (Exception $e) {
    write_log_entry('Create Zip', __LINE__, $e->getMessage());
  }
  foreach (rls($input_dir_path) as $file) {
    try {
      $zip->addFile($file, basename($file));
    }
    catch (Exception $e) {
      write_log_entry('Create Zip', __LINE__, $e->getMessage());
    }
  }
  try {
    $zip->close();
    $stats = get_file_stats($output_file_path);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
  }
  catch (Exception $e) {
    $stats = get_file_stats($output_file_path);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
    write_log_entry('Create Zip', __LINE__, $e->getMessage());
  }
}

