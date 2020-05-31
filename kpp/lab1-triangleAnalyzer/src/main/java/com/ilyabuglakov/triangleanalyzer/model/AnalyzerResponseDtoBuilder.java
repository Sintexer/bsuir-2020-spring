package com.ilyabuglakov.triangleanalyzer.model;

import java.util.List;

public class AnalyzerResponseDtoBuilder {
    private long totalRequestsCount;
    private long uniqueRequestCount;
    private long invalidRequestCount;
    private List<TriangleAttributes> responseList;

    public void setTotalRequestsCount(long totalRequestsCount) {
        this.totalRequestsCount = totalRequestsCount;
    }

    public void setUniqueRequestCount(long uniqueRequestCount) {
        this.uniqueRequestCount = uniqueRequestCount;
    }

    public void setInvalidRequestCount(long invalidRequestCount) {
        this.invalidRequestCount = invalidRequestCount;
    }

    public void setResponseList(List<TriangleAttributes> responseList) {
        this.responseList = responseList;
    }

    public void reset(){
        totalRequestsCount = 0;
        uniqueRequestCount = 0;
        invalidRequestCount = 0;
        responseList = null;
    }

    public AnalyzerResponseDto build(){
        AnalyzerResponseDto result = new AnalyzerResponseDto();
        result.setTotalRequestsCount(totalRequestsCount);
        result.setUniqueRequestCount(uniqueRequestCount);
        result.setInvalidRequestCount(invalidRequestCount);
        result.setResponseList(responseList);
        return result;
    }
}
