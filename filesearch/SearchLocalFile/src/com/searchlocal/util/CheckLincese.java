package com.searchlocal.util;

import java.io.File;

import com.searchlocal.constants.Constant;

public class CheckLincese {

	/**
	 * @param args
	 */
	public static boolean checkLincese() {
		
		// lincese不存在
		File linceseFile = new File(Constant.datapath + Constant.licencepath);
		if(!linceseFile.exists()){
			return false;
		}

		boolean isfirststart = false;
		String eneryString  = ComputerInfoUtil.getCurrentEncryPtString();
		String lincuece = Crypt.getLinecese();
		System.out.println("eneryString::::" + eneryString);
		System.out.println("lincuece::::" + lincuece);
		if(lincuece.startsWith("11553950") && lincuece.endsWith("5000000")){
			isfirststart = true;
			Crypt.createLincese();
			// 设置桌面快捷方式
			MakeShortCut.create();
		}
		
		// 是否第一次启动,如果是第一次启动不需要验证
		if(!isfirststart){
			// 日期验证
			String ltemp = lincuece.substring(0, 8);
			String etemp = eneryString.substring(0, 8);
			System.out.println("日期验证：：" + ltemp);
			System.out.println("日期验证：：" + etemp);
			if(etemp.compareTo(ltemp) > 0){
				return false;
			}
			
			// SN验证
			ltemp = lincuece.substring(9);
			etemp = eneryString.substring(9);
			System.out.println("SN验证：：" + ltemp);
			System.out.println("SN验证：：" + etemp);
			if(!etemp.equals(ltemp)){
				return false;
			}
		}

		return true;
	}
}
