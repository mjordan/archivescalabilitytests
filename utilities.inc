<?php

/**
 * Utility functions.
 */

/**
 * This recursively lists the contents of a directory. Doesn't include
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

