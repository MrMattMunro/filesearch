package com.searchlocal.param;

public class SearchParam {

	private String query;

	private String searchname;

	private int startRow;

	private int endRow;
	
	private String searchtype;

	/**
	 * @return Returns the endRow.
	 */
	public int getEndRow() {
		return endRow;
	}

	/**
	 * @param endRow
	 *            The endRow to set.
	 */
	public void setEndRow(int endRow) {
		this.endRow = endRow;
	}

	/**
	 * @return Returns the startRow.
	 */
	public int getStartRow() {
		return startRow;
	}

	/**
	 * @param startRow
	 *            The startRow to set.
	 */
	public void setStartRow(int startRow) {
		this.startRow = startRow;
	}

	/**
	 * @return Returns the query.
	 */
	public String getQuery() {
		return query;
	}

	/**
	 * @param query
	 *            The query to set.
	 */
	public void setQuery(String query) {
		this.query = query;
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

	/**
	 * @return Returns the searchtype.
	 */
	public String getSearchtype() {
		return searchtype;
	}

	/**
	 * @param searchtype The searchtype to set.
	 */
	public void setSearchtype(String searchtype) {
		this.searchtype = searchtype;
	}

}
