package com.ilyabuglakov.triangleanalyzer.controller;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(code = HttpStatus.INTERNAL_SERVER_ERROR, reason = "Operation not implemented")
public class OperaionNotImplemented extends RuntimeException{

}