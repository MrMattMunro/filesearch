package com.searchlocal.param;

import java.util.List;

public class CreateNewParam {

	String searchname;

	String path;

	List selectfiletype;

	String indexpath;

	/**
	 * @return Returns the idexpath.
	 */
	public String getIdexpath() {
		return indexpath;
	}

	/**
	 * @param idexpath
	 *            The idexpath to set.
	 */
	public void setIdexpath(String idexpath) {
		this.indexpath = idexpath;
	}

	/**
	 * @return Returns the selectfiletype.
	 */
	public List getSelectfiletype() {
		return selectfiletype;
	}

	/**
	 * @param selectfiletype
	 *            The selectfiletype to set.
	 */
	public void setSelectfiletype(List selectfiletype) {
		this.selectfiletype = selectfiletype;
	}

	/**
	 * @return Returns the path.
	 */
	public String getPath() {
		return path;
	}

	/**
	 * @param path
	 *            The path to set.
	 */
	public void setPath(String path) {
		this.path = path;
	}

	/**
	 * @return Returns the searchname.
	 */
	public String getSearchname() {
		return searchname;
	}

	/**
	 * @param searchname
	 *            The searchname to set.
	 */
	public void setSearchname(String searchname) {
		this.searchname = searchname;
	}

}
