package com.searchlocal.menu.jp;

import java.awt.Color;
import java.awt.Container;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.border.TitledBorder;

import org.pushingpixels.substance.api.skin.SubstanceBusinessBlackSteelLookAndFeel;

import com.searchlocal.constants.Constant;
import com.searchlocal.menu.CFrame;
import com.searchlocal.menu.CPanel;
import com.searchlocal.util.FileOpenerUtil;
import com.searchlocal.util.MenuMessageUtil;

public class JPAboutFrame extends CFrame implements ActionListener {

	private static final long serialVersionUID = 1L;

	static JPAboutFrame c;

	private static String websiteurl = "http://www.slfile.net";

	private static String mail = "qianjinfu@gmail.com";

	JLabel selectindexdir = new JLabel();

	private static MenuMessageUtil msg = new MenuMessageUtil();

	public JPAboutFrame() {

		Container container = getContentPane();
		container.setLayout(null);
		setTitle(msg.getMsgbyId(Constant.title_aboutsoft));

		CPanel panel = new CPanel();
		panel.setLayout(null);
		panel.setBounds(5, 5, 530, 340);
		TitledBorder border = new TitledBorder("");
		border.setBorder(BorderFactory.createEtchedBorder(Color.orange, Color.BLUE));
		panel.setBorder(border);

		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r1), 60, 10, 300, 25);
		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r2), 60, 30, 460, 25);
		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r3), 60, 50, 460, 25);
		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r4), 60, 70, 300, 25);
		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r5), 60, 90, 460, 25);
		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r6), 60, 110, 460, 25);
		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r7), 60, 130, 460, 25);
		panel.makeLabel(msg.getMsgbyId(Constant.about_frame_r8), 60, 150, 460, 25);
		
		panel.makeLabel(msg.getMsgbyId(Constant.label_homepage), 60, 180, 120, 25);
		String website = "<html><a href=\"" + websiteurl + "\">"
		+ websiteurl + "</a></html>";
		JLabel jwebsite = panel.makeLabel(website, 140, 180, 120, 25);
		jwebsite.addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent e) {
				try {
					FileOpenerUtil openerUtil = new FileOpenerUtil(null);
					String opener = openerUtil.getOpenerbyId("ie");
					Runtime.getRuntime().exec(opener + " " + websiteurl);
				} catch (Exception ex) {
					ex.printStackTrace();
				}
			}
		});

		panel.makeLabel(msg.getMsgbyId(Constant.label_contact), 60, 200, 120, 25);
		String group = "<html><a href=mailto:" + mail + ">" + mail + "</a></html>";
		panel.makeLabel(group, 140, 200, 300, 25);
		
		
		JButton cancelbutton = panel.makeButton(msg.getMsgbyId(Constant.button_close), 220, 260, 70, 20,"");
		cancelbutton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				c.setVisible(false);
			}
		});

		container.add(panel);
        this.setSize(550, 350);
		this.setLocationRelativeTo(null);
		this.setResizable(false);
	}

	public static void showframe() throws UnsupportedLookAndFeelException,
			ClassNotFoundException, InstantiationException,
			IllegalAccessException {
		JFrame.setDefaultLookAndFeelDecorated(true);
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.setLookAndFeel(new SubstanceBusinessBlackSteelLookAndFeel());
				} catch (UnsupportedLookAndFeelException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				c = new JPAboutFrame();
				c.setIconImage(Toolkit.getDefaultToolkit().getImage(Constant.titleicopath));
				c.setVisible(true);
			}
		});
	}

	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
	}
}