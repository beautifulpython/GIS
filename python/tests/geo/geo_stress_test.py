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

import pandas
from osgeo import ogr
import arctern


def test_ST_IsValid():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_IsValid(arctern.ST_GeomFromText(data))


def test_ST_PrecisionReduce():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_PrecisionReduce(arctern.ST_GeomFromText(data), 3))


def test_ST_Intersection():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_AsText(arctern.ST_Intersection(arctern.ST_GeomFromText(data1), arctern.ST_GeomFromText(data2)))


def test_ST_Equals():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_Equals(arctern.ST_GeomFromText(data1), arctern.ST_GeomFromText(data2))


def test_ST_Touches():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_Touches(arctern.ST_GeomFromText(data1), arctern.ST_GeomFromText(data2))


def test_ST_Overlaps():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_Overlaps(arctern.ST_GeomFromText(data1), arctern.ST_GeomFromText(data2))


def test_ST_Crosses():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_Crosses(arctern.ST_GeomFromText(data1), arctern.ST_GeomFromText(data2))


def test_ST_IsSimple():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_IsSimple(arctern.ST_GeomFromText(data))


def test_ST_GeometryType():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_GeometryType(arctern.ST_GeomFromText(data))


def test_ST_MakeValid():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_MakeValid(arctern.ST_GeomFromText(data)))


def test_ST_SimplifyPreserveTopology():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_SimplifyPreserveTopology(arctern.ST_GeomFromText(data), 10000))


def test_ST_Point():
    geo1 = 1.1
    geo2 = 2.1
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    string_ptr = arctern.ST_AsText(arctern.ST_Point(data1, data2))


def test_ST_GeomFromGeoJSON():
    geo = "{\"type\":\"Polygon\",\"coordinates\":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    str_ptr = arctern.ST_AsText(arctern.ST_GeomFromGeoJSON(data))


def test_ST_AsGeoJSON():
    geo = "{\"type\":\"Polygon\",\"coordinates\":[[[0,0],[0,1],[1,1],[1,0],[0,0]]]}"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    str_ptr = arctern.ST_AsGeoJSON(arctern.ST_GeomFromGeoJSON(data))


def test_ST_GeomFromText():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    str_ptr = arctern.ST_AsText(arctern.ST_GeomFromText(data))


def test_ST_Contains():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_Contains(arctern.ST_GeomFromText(data2), arctern.ST_GeomFromText(data1))


def test_ST_Intersects():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 1000000001)]
    arr2 = [geo2 for x in range(1, 1000000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_AsText(arctern.ST_Intersects(arctern.ST_GeomFromText(data1), arctern.ST_GeomFromText(data2)))
    assert len(rst) == 1000000000


def test_ST_Within():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_Within(arctern.ST_GeomFromText(data2), arctern.ST_GeomFromText(data1))


def test_ST_Distance():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_Distance(arctern.ST_GeomFromText(data2), arctern.ST_GeomFromText(data1))


def test_ST_DistanceSphere():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_DistanceSphere(arctern.ST_GeomFromText(data2), arctern.ST_GeomFromText(data1))


def test_ST_Area():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_Area(arctern.ST_GeomFromText(data))


def test_ST_Centroid():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_Centroid(arctern.ST_GeomFromText(data)))


def test_ST_Length():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_Length(arctern.ST_GeomFromText(data))


def test_ST_HausdorffDistance():
    geo1 = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    geo2 = "POLYGON ((0 0,0 2,2 2,2 0,0 0))"
    arr1 = [geo1 for x in range(1, 100000001)]
    arr2 = [geo2 for x in range(1, 100000001)]

    data1 = pandas.Series(arr1)
    data2 = pandas.Series(arr2)
    rst = arctern.ST_HausdorffDistance(arctern.ST_GeomFromText(data1), arctern.ST_GeomFromText(data2))


def test_ST_ConvexHull():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_ConvexHull(arctern.ST_GeomFromText(data)))


def test_ST_Transform():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_Transform(arctern.ST_GeomFromText(data), "EPSG:4326", "EPSG:3857"))


def test_ST_CurveToLine():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_CurveToLine(arctern.ST_GeomFromText(data)))


def test_ST_NPoints():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_NPoints(arctern.ST_GeomFromText(data))


def test_ST_Envelope():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_Envelope(arctern.ST_GeomFromText(data)))


def test_ST_Buffer():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_Buffer(arctern.ST_GeomFromText(data), 1.2))


def test_ST_PolygonFromEnvelope():
    x_min = pandas.Series([0.0 for x in range(1, 100000001)])
    x_max = pandas.Series([1.0 for x in range(1, 100000001)])
    y_min = pandas.Series([0.0 for x in range(1, 100000001)])
    y_max = pandas.Series([1.0 for x in range(1, 100000001)])

    rst = arctern.ST_AsText(arctern.ST_PolygonFromEnvelope(x_min, y_min, x_max, y_max))


def test_ST_Union_Aggr():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_Union_Aggr(arctern.ST_GeomFromText(data)))


def test_ST_Envelope_Aggr():
    geo = "POLYGON ((0 0,0 1,1 1,1 0,0 0))"
    arr = [geo for x in range(1, 100000001)]
    data = pandas.Series(arr)
    rst = arctern.ST_AsText(arctern.ST_Envelope_Aggr(arctern.ST_GeomFromText(data)))
