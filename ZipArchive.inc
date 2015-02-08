<?php

/**
 * @param string $input_dir_path
 *   The path to the directory containing the input files.
 *
 * @pararm string $output_file_basename
 *   The basename of the output .zip file.
 *
 */
function create_archive_zip($input_dir_path, $output_file_basename) {
  $output_filename = $output_file_basename . '.zip';
  $zip = new ZipArchive();
  try {
    $zip->open($output_filename, ZIPARCHIVE::CREATE);
  }
  catch (Exception $e) {
    write_log_entry('Create Zip', __LINE__, $e->getMessage());
  }
  foreach (rls($input_dir_path) as $file) {
    try {
      $zip->addFile($file);
    }
    catch (Exception $e) {
      write_log_entry('Create Zip', __LINE__, $e->getMessage());
    }
  }
  try {
    $zip->close();
    $stats = get_file_stats($output_filename);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
  }
  catch (Exception $e) {
    $stats = get_file_stats($output_filename);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
    write_log_entry('Create Zip', __LINE__, $e->getMessage());
  }
}

