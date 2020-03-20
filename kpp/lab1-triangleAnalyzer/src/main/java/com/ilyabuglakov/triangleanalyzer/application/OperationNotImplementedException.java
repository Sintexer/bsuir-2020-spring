package com.ilyabuglakov.triangleanalyzer.application;

public class OperationNotImplementedException extends RuntimeException{
    public OperationNotImplementedException(String message){
        super(message);
    }
}