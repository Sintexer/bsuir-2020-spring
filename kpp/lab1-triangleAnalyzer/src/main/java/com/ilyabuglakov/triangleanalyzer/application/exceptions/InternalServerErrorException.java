package com.ilyabuglakov.triangleanalyzer.application.exceptions;


public class InternalServerErrorException extends RuntimeException{
    public InternalServerErrorException(String reason) {
        super(reason);
    }

    public InternalServerErrorException(String reason, Throwable cause) {
        super(reason, cause);
    }
}
