#!/usr/bin/awk -f

BEGIN {
   FS="[[:space:]:,()]"
}

{
   if ($0 ~ /^[[:alnum:]_.]+:/) {
      defined_labels[$1] = 1;
   } else if ($0 ~ /^[^;]*[[:alnum:]_.]+/) {
      for (i = 1; i <= NF; ++i) {
         if ($i ~ /[[:alnum:]_.]+/) {
            used_labels[$i] = 1;
         }
      }
   }
}

END {
   # compute set difference, defined - used
   for (used_label in used_labels) {
      delete defined_labels[used_label];
   }
   
   for (defined_label in defined_labels) {
      print defined_label;
   }
}
