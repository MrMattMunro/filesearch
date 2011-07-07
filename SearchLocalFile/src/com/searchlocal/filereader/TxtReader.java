package com.searchlocal.filereader;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

import com.searchlocal.bean.TxtFileBean;
import com.searchlocal.exception.LogicException;
import com.searchlocal.util.CLogger;
import com.searchlocal.util.StringUtils;

public class TxtReader {

	private static CLogger logger = new CLogger(TxtReader.class);

	public List<TxtFileBean> getTxtFile(TxtFileBean file) throws LogicException {

		TxtFileBean filebean;
		InputStream inputStream = null;
		BufferedReader reader = null;
		List<TxtFileBean> returnList = new ArrayList<TxtFileBean>();
		try {
			inputStream = new FileInputStream(file.getPath());
			reader = new BufferedReader(new InputStreamReader(inputStream));
			String temp = "";
			int i = 1;
			while ((temp = reader.readLine()) != null) {
				if (!temp.equals("")) {
					filebean = new TxtFileBean();
					filebean.setFilename(file.getFilename());
					filebean.setPath(file.getPath());
					filebean.setContent(temp);
					filebean.setLastmodify(file.getLastmodify());
					filebean.setRownb(i);
					returnList.add(filebean);
					i++;
				} else {
					i++;
				}
			}

		} catch (FileNotFoundException e) {
			logger.error("LG_E001", file.getPath());
			throw new LogicException("LG_E001", e);
		} catch (UnsupportedEncodingException e) {
			logger.error("LG_E002", file.getPath());
			throw new LogicException("LG_E002", e);
		} catch (IOException e) {
			logger.error("LG_E003", file.getPath());
			throw new LogicException("LG_E003", e);
		} finally {
			try {
				if (inputStream != null) {
					inputStream.close();
				}
				if (reader != null) {
					reader.close();
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		return returnList;
	}
}
