<?php

require_once 'Archive/Tar.php';

/**
 * @param string $input_dir_path
 *   The path to the directory containing the input files.
 *
 * @pararm string $output_file_basename
 *   The basename of to the output .tgz file.
 *
 */
function create_archive_zip($input_dir_path, $output_file_basename) {
  $output_filename = $output_file_basename . '.tgz';
  print "output file path is $output_filename\n";
  try {
    $tar = new Archive_Tar($output_file_basename . '.tar', 'gz');
  }
  catch (Exception $e) {
    write_log_entry('Create compressed tar archive', __LINE__, $e->getMessage());
  }
  try {
    $file_list = rls($input_dir_path);
    print_r($file_list);
    $tar->create($file_list);
  }
  catch (Exception $e) {
    write_log_entry('Create compressed tar archive', __LINE__, $e->getMessage());
  }
  try {
    $stats = get_file_stats($output_filename);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
  }
  catch (Exception $e) {
    $stats = get_file_stats($output_filename);
    write_log_entry('Stat output file', __LINE__, $stats['size']);
    write_log_entry('Create compressed tar archive', __LINE__, $e->getMessage());
  }
}

