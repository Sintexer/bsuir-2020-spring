package com.ilyabuglakov.triangleanalyzer.application;


public class InternalServerErrorException extends RuntimeException{
    public InternalServerErrorException(String message){
        super(message);
    }
}
