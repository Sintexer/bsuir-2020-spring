package com.ilyabuglakov.triangleanalyzer.model;

import java.util.List;

public class AnalyzerResponseDto {
//    int totalRequestsCount;
//    int uniqueRequestCount;
//    int invalidRequestCount;
    List<TriangleAttributes> responseList;

    public AnalyzerResponseDto(List<TriangleAttributes> responseList) {
        this.responseList = responseList;
    }
}
