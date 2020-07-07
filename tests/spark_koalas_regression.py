# Copyright (C) 2019-2020 Zilliz. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# pylint: disable=too-many-lines
# pylint: disable=redefined-outer-name
# pylint: disable=wildcard-import
# pylint: disable=unused-wildcard-import

import pandas as pd
from osgeo import ogr
from arctern_spark.geoseries import GeoSeries
from databricks.koalas import Series

input_csv_base_dir = './data/'
output_csv_base_dir = './output/'
def read_csv2arr(input_csv_path):
    import re
    arr = []
    col1 = []
    col2 = []
    with open(input_csv_path) as f:
        rows = [line for line in f][1:] # csv header should be filtered
    for row in rows:
        arr.append(re.split('[|]',row.strip()))
    if len(arr[0]) == 2:
        for items in arr:
            assert len(items) == 2
            col1.append(items[0])
            col2.append(items[1])
    elif len(arr[0]) == 1:
        for items in arr:
            assert len(items) == 1
            col1.append(items[0])
    else :
        raise Exception('Csv file columns length must be 1 or 2.')
    return col1,col2

def write_arr2csv(output_csv_path,output_arr):
    import csv
    with open(output_csv_path,'w') as f:
        csv_writer = csv.writer(f, delimiter='|', lineterminator='\n')
        for x in output_arr : csv_writer.writerow ([x])


def test_binary_func(input_csv,output_csv,func_name):
    input_csv_path = input_csv_base_dir + input_csv
    output_csv_path = output_csv_base_dir + output_csv
    col1,col2 = read_csv2arr(input_csv_path)
    assert len(col1) == len(col2)
    geo_s1 = GeoSeries(col1)
    geo_s2 = GeoSeries(col2)
    test_codes = 'geo_s1.'+func_name+'(geo_s2)'
    res = eval(test_codes)
    write_arr2csv(output_csv_path,res.tolist())


def test_unary_property_func(input_csv,output_csv,func_name):
    input_csv_path = input_csv_base_dir + input_csv
    output_csv_path = output_csv_base_dir + output_csv
    col1,col2 = read_csv2arr(input_csv_path)
    assert len(col2) == 0
    geo_s1 = GeoSeries(col1)
    test_codes = 'geo_s1.'+func_name
    res = eval(test_codes)
    write_arr2csv(output_csv_path,res.tolist())


def test_unary_func(input_csv,output_csv,func_name,params=None):
    input_csv_path = input_csv_base_dir + input_csv
    output_csv_path = output_csv_base_dir + output_csv
    col1,col2 = read_csv2arr(input_csv_path)
    assert len(col2) == 0
    geo_s1 = GeoSeries(col1)
    if params == None :
        test_codes = 'geo_s1.'+func_name+'()'
    else :
        test_codes = 'geo_s1.'+func_name+'('+params+').to_wkt()'
    res = eval(test_codes)
    write_arr2csv(output_csv_path,res.tolist())



func_dict = {
'is_valid':['isvalid.csv','isvalid.out'],

}

if __name__ == "__main__":
