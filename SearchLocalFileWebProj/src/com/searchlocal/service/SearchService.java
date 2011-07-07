package com.searchlocal.service;

import java.io.IOException;
import java.util.List;

import com.searchlocal.exception.LogicException;
import com.searchlocal.param.SearchParam;

public interface SearchService {

	public List dosearcher(SearchParam param) throws IOException, LogicException;

	public int getCount(SearchParam param) throws IOException;

}
