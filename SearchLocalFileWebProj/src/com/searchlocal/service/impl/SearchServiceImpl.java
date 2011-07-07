package com.searchlocal.service.impl;

import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import com.searchlocal.exception.LogicException;
import com.searchlocal.lucene.ContentSearcher;
import com.searchlocal.param.CreateNewParam;
import com.searchlocal.param.SearchParam;
import com.searchlocal.service.SearchService;
import com.searchlocal.util.XMLConfig;

public class SearchServiceImpl implements SearchService {

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.searchlocal.service.SearchService#dosearcher(com.searchlocal.param.SearchParam)
	 */
	public List dosearcher(SearchParam param) throws IOException, LogicException {
		String indexpath = getIndexpath(param.getSearchname());
		return ContentSearcher.query(param, indexpath);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.searchlocal.service.SearchService#dosearcher(com.searchlocal.param.SearchParam)
	 */
	public int getCount(SearchParam param) throws IOException {
		String indexpath = getIndexpath(param.getSearchname());
		int count = ContentSearcher.getCount(param, indexpath);
		return count;
	}

	private String getIndexpath(String searchname) {

		List entityList = XMLConfig.getList();
		String indexpath = "";
		for (Iterator iter = entityList.iterator(); iter.hasNext();) {
			CreateNewParam element = (CreateNewParam) iter.next();
			if (element.getSearchname().equals(searchname)) {
				indexpath = element.getIdexpath();
			}
		}
		return indexpath;
	}
}
