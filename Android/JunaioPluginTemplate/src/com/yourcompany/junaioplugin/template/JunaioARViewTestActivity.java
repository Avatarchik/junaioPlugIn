package com.yourcompany.junaioplugin.template;

import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.FrameLayout.LayoutParams;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;

import com.yourcompany.junaioplugin.template.R;
import com.metaio.junaio.plugin.JunaioPlugin;
import com.metaio.junaio.plugin.util.JunaioUtils;
import com.metaio.junaio.plugin.view.JunaioARViewActivity;
import com.metaio.sdk.jni.DataSourceEvent;
import com.metaio.sdk.jni.IGeometry;
import com.metaio.sdk.jni.LLACoordinate;
import com.metaio.sdk.jni.MetaioWorldPOI;
import com.metaio.sdk.jni.Vector3d;

public class JunaioARViewTestActivity extends JunaioARViewActivity
{
	/**
	 * GUI overlay
	 */
	private RelativeLayout mGUIView;

	/**
	 * Progress bar view
	 */
	private ProgressBar progressView;
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		// Window managed wake lock (no permissions, no accidentally kept on)
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		// Optionaly add GUI
		if (mGUIView == null)
			mGUIView = (RelativeLayout) getLayoutInflater().inflate(R.layout.arview, null);
		
		
		progressView = (ProgressBar) mGUIView.findViewById(R.id.progressBar);
		
		//Init the AREL webview. Pass a container if you want to use a ViewPager or Horizontal Scroll View over the camera preview or the root view. 
		initARELWebView(mGUIView);
		
		//Used to resume the camera preview
		mIsInLiveMode = true;
	}

	@Override
	public void onStart()
	{
		super.onStart();

		SplashActivity.log("JunaioARViewTestActivity.onCreate()");
		
		//if we want to catch the sensor listeners
		JunaioPlugin.getSensorsManager(getApplicationContext()).registerCallback(this);
		
		// add GUI layout
		if (mGUIView != null)
			addContentView(mGUIView, new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
		
		//comes from splash activity
		final int channelID = getIntent().getIntExtra(getPackageName()+".CHANNELID", -1);
		if (channelID > 0)
		{
			// Clear the intent extra before proceeding
			getIntent().removeExtra(getPackageName()+".CHANNELID");
			setChannel(channelID);

		}
	}

	@Override
	protected void onPause() {
		super.onPause();
	}
	
	@Override
	protected void onResume()
	{
		super.onResume();
	}

	@Override
	protected void onStop()
	{
		super.onStop();
	}

	@Override
	public void onLocationSensorChanged(LLACoordinate location) {
		super.onLocationSensorChanged(location);
	}
	
	@Override
	public void onHeadingSensorChanged(float[] orientation) {
		super.onHeadingSensorChanged(orientation);
	}
	
	@Override
	public void onConfigurationChanged(Configuration newConfig) 
    { 
    	super.onConfigurationChanged(newConfig);
    }
	
	@Override
	public void onSurfaceChanged(int width, int height) {
		//always call the super implementation first
		super.onSurfaceChanged(width, height);
		
		//get radar margins from the resources (this will make the values density independant)
		float marginTop = getResources().getDimension(R.dimen.radarTop);
		float marginRight = getResources().getDimension(R.dimen.radarRight);
		float radarScale = getResources().getDimension(R.dimen.radarScale);
		//set the radar to the top right corner and add some margin, scale to 1
		setRadarProperties(IGeometry.ANCHOR_TOP|IGeometry.ANCHOR_RIGHT, new Vector3d(-marginRight,-marginTop,0f), new Vector3d(radarScale,radarScale,1f));
	}

		
	@Override
	protected void updateGUI()
	{
		// TODO: here update any GUI related to channel information, e.g. icon, name etc 
	}
	
	@Override
	public void onScreenshot(Bitmap bitmap)
	{
		// this is triggered by calling takeScreenshot() or through AREL
	}

	
	@Override
    protected void showProgress(final boolean show)
    {
    
		progressView.post(new Runnable()
		{
	    	
			public void run()
			{
				progressView.setIndeterminate(true);
				progressView.setVisibility(show ? View.VISIBLE : View.INVISIBLE);
			}
		});
    }
	
	@Override
	protected void showProgressBar(final float progress, final boolean show) {
		
		progressView.post(new Runnable() {
			
			@Override
			public void run() {
				progressView.setIndeterminate(false);
				progressView.setProgress((int) progress);
				progressView.setVisibility(show? View.VISIBLE:View.INVISIBLE);
				
			}
		});
	}
	
	
	@Override
	protected void onServerEvent(DataSourceEvent event) {
		switch (event) {
			case DataSourceEventNoPoisReturned:
				JunaioUtils.showToast(this, getString(R.string.MSGI_POIS_NOT_FOUND));
				break;
			case DataSourceEventServerError:
				JunaioUtils.showToast(this, getString(R.string.MSGE_TRY_AGAIN));
				break;
			case DataSourceEventServerNotReachable:
				JunaioUtils.showToast(this, getString(R.string.MSGW_SERVER_UNREACHABLE));
				break;
			default:
				break;
		}
	}
	
	@Override
	protected void onPOIsAdded() {
		super.onPOIsAdded();
	}
	
	@Override
	protected void onObjectAdded(MetaioWorldPOI object) {
		super.onObjectAdded(object);
	}
	
	@Override
	protected void onObjectRemoved(MetaioWorldPOI object) {
		super.onObjectRemoved(object);
	}
	
	@Override
	protected void onRemoveContent() {
		super.onRemoveContent();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
	}
}
