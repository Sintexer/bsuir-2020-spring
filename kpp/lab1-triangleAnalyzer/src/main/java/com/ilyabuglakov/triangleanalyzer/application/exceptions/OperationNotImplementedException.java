package com.ilyabuglakov.triangleanalyzer.application.exceptions;

public class OperationNotImplementedException extends RuntimeException{
    public OperationNotImplementedException(String reason) {
        super(reason);
    }

    public OperationNotImplementedException(String reason, Throwable cause) {
        super(reason, cause);
    }
}