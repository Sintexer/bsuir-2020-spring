package com.ilyabuglakov.triangleanalyzer.controller;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(code = HttpStatus.BAD_REQUEST, reason = "Provided triangle can't exist")
public class BadRequest extends RuntimeException {
}
