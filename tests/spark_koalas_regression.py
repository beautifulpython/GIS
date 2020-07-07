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


def test_ST_IsValid():
    input_csv_path = input_csv_base_dir + "isvalid.csv"
    output_csv_path = output_csv_base_dir + "isvalid.out"
    col1,col2 = read_csv2arr(input_csv_path)
    assert len(col2) == 0
    geo_s = GeoSeries(col1)
    res = geo_s.is_valid
    write_arr2csv(output_csv_path,res.tolist())

def test_ST_Intersects():
    input_csv_path = input_csv_base_dir + "intersects.csv"
    output_csv_path = output_csv_base_dir + "intersects.out"
    col1,col2 = read_csv2arr(input_csv_path)
    assert len(col1) == len(col2)
    geo_s1 = GeoSeries(col1)
    geo_s2 = GeoSeries(col2)
    res = geo_s1.intersects(geo_s2)
    write_arr2csv(output_csv_path,res.tolist())


def test_ST_Intersection():
    input_csv_path = input_csv_base_dir + "intersection.csv"
    output_csv_path = output_csv_base_dir + "intersection.out"
    col1,col2 = read_csv2arr(input_csv_path)
    assert len(col1) == len(col2)
    geo_s1 = GeoSeries(col1)
    geo_s2 = GeoSeries(col2)
    res = geo_s1.intersection(geo_s2)
    write_arr2csv(output_csv_path,res.tolist())

if __name__ == "__main__":

# TODO : test koalas geoseries refer to old regression
    url = 'local'
    spark_session = SparkSession.builder.appName("Python zgis sample").master(url).getOrCreate()
    spark_session.conf.set("spark.sql.execution.arrow.pyspark.enabled", "true")

    clear_result_dir('/tmp/results')
    register_funcs(spark_session)

    run_test_st_geomfromgeojson(spark_session)
    run_test_st_geomfromgeojson2(spark_session)
    run_test_st_curvetoline(spark_session)
    run_test_st_point(spark_session)
    run_test_envelope_aggr_1(spark_session)
    run_test_envelope_aggr_curve(spark_session)
    run_test_envelope_aggr_2(spark_session)
    run_test_union_aggr_2(spark_session)
    run_test_union_aggr_curve(spark_session)
    run_test_st_isvalid_1(spark_session)
    run_test_st_isvalid_curve(spark_session)
    run_test_st_intersection(spark_session)
    run_test_st_intersection_curve(spark_session)
    run_test_st_convexhull(spark_session)
    run_test_st_convexhull_curve(spark_session)
    run_test_st_buffer(spark_session)
    run_test_st_buffer1(spark_session)
    run_test_st_buffer2(spark_session)
    run_test_st_buffer3(spark_session)
    run_test_st_buffer4(spark_session)
    run_test_st_buffer5(spark_session)
    run_test_st_buffer6(spark_session)
    run_test_st_buffer_curve(spark_session)
    run_test_st_buffer_curve1(spark_session)
    run_test_st_envelope(spark_session)
    run_test_st_envelope_curve(spark_session)
    run_test_st_centroid(spark_session)
    run_test_st_centroid_curve(spark_session)
    run_test_st_length(spark_session)
    run_test_st_length_curve(spark_session)
    run_test_st_area(spark_session)
    run_test_st_area_curve(spark_session)
    run_test_st_distance(spark_session)
    run_test_st_distance_curve(spark_session)
    run_test_st_issimple(spark_session)
    run_test_st_issimple_curve(spark_session)
    run_test_st_npoints(spark_session)
    run_test_st_geometrytype(spark_session)
    run_test_st_geometrytype_curve(spark_session)
    run_test_st_transform(spark_session)
    run_test_st_transform1(spark_session)
    run_test_st_intersects(spark_session)
    run_test_st_intersects_curve(spark_session)
    run_test_st_contains(spark_session)
    run_test_st_contains_curve(spark_session)
    run_test_st_within(spark_session)
    run_test_st_within_curve(spark_session)
    run_test_st_equals_1(spark_session)
    run_test_st_equals_2(spark_session)
    run_test_st_crosses(spark_session)
    run_test_st_crosses_curve(spark_session)
    run_test_st_overlaps(spark_session)
    run_test_st_overlaps_curve(spark_session)
    run_test_st_touches(spark_session)
    run_test_st_touches_curve(spark_session)
    run_test_st_makevalid(spark_session)
    run_test_st_precisionreduce(spark_session)
    run_test_st_polygonfromenvelope(spark_session)
    run_test_st_simplifypreservetopology(spark_session)
    run_test_st_simplifypreservetopology_curve(spark_session)
    run_test_st_hausdorffdistance(spark_session)
    run_test_st_hausdorffdistance_curve(spark_session)
    run_test_st_pointfromtext(spark_session)
    run_test_st_polygonfromtext(spark_session)
    run_test_st_linestringfromtext(spark_session)
    run_test_st_geomfromtext(spark_session)
    run_test_st_geomfromwkt(spark_session)
    run_test_st_astext(spark_session)

    spark_session.stop()
