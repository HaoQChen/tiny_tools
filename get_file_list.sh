#!/bin/bash
list_file=pcd_list.txt
path=~/JDD_ws/src/load_pcd_map/maps
find $path -name "*.pcd" > $list_file
