package com.web.searchlocal.param;

public class SearchParam {
	
	private String id;
	
	private String query;

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

	/**
	 * 取得id
	 * 
	 * @return String id 
	 */
	public String getId() {
		return id;
	}

	/**
	 * 设定id 
	 * 
	 * @param String id 
	 */
	public void setId(String id) {
		this.id = id;
	}

}
