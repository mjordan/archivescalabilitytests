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

/**
 * Main script logic.
 */
register_shutdown_function('shutdown');

switch ($type) {
  case 'ZipArchive':
    create_archive_zip($input_dir, $output_file);
    break;
  case 'Archive_Tar':
    create_archive_zip($input_dir, $output_file);
    break;
  default:
    "Sorry, I don't recognize that type of archive\n";
    exit();
}

/**
 * Functions
 */

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

/**
 * This recursively lists the contents of a directory. This doesn't return 
 * hidden files.
 *
 * Borrowed from https://github.com/scholarslab/BagItPHP/blob/master/lib/bagit_utils.php.
 * 
 * @param string $dir The name of the directory to list.
 * 
 * @return array A list of files in the directory.
 */
function rls($dir) {
    $files = array();
    $queue = array($dir);
    while (count($queue) > 0) {
        $current = array_shift($queue);
        foreach (scandir($current) as $item) {
            if ($item[0] != '.') {
                $filename = "$current/$item";
                switch (filetype($filename))
                {
                case 'file':
                    array_push($files, $filename);
                    break;
                case 'dir':
                    array_push($queue, $filename);
                    break;
                }
            }
        }
    }
    return $files;
}

function shutdown() {
  $memory_used = memory_get_peak_usage();
  write_log_entry('Shutdown', __LINE__, "Peak memory used was $memory_used bytes");
}

/**
 *
 */
function get_file_stats($file_path) {
  $stats = stat($file_path);
  return $stats;
}

/**
 * Log stuff.
 *
 * 
 */
function write_log_entry($type, $line_number, $message) {
  global $log_file;
  $datestamp = date("Y-m-d H:i:s");
  $parts = array($datestamp, 'Line ' . $line_number, $type, trim($message)  );
  $entry = implode("\t", $parts) . "\n";
  file_put_contents($log_file, $entry, FILE_APPEND);
}

?>

