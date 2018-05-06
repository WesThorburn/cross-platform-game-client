#include <emscripten.h>
#include <iostream>
#include "Canvas.h"

namespace Canvas{
	ScaleAttributes scaleAttributes;

	void initialize(Layer layer, std::string name){
		EM_ASM({
			var ctx = document.getElementById(UTF8ToString($1)).getContext("2d");
			contexts[$0] = ctx;
		}, layer, name.c_str());
		fitToWindow(layer);
	}

	void clear(Layer layer){
		EM_ASM({
			var ctx = contexts[$0];
	        var canvas = ctx.canvas;
	        ctx.clearRect(0, 0, $1, $2);
		}, layer, Canvas::scaleAttributes.scaledWidth, Canvas::scaleAttributes.scaledHeight);
	}

	void fitToWindow(Layer layer){
		EM_ASM({
			var ctx = contexts[$0];
			var canvas = ctx.canvas;
			canvas.width = window.innerWidth * window.devicePixelRatio;
			canvas.height = window.innerHeight * window.devicePixelRatio;
			canvas.style.width = canvas.width / window.devicePixelRatio + "px";
			canvas.style.height = canvas.height / window.devicePixelRatio + "px";
		}, layer);
	}

	void updateAspectRatio(int browserWidth, int browserHeight){
		scaleAttributes.nativeAspectRatio = static_cast<double>(scaleAttributes.NATIVE_WIDTH) / static_cast<double>(scaleAttributes.NATIVE_HEIGHT);
		scaleAttributes.currentAspectRatio = static_cast<double>(browserWidth) / static_cast<double>(browserHeight);
	}

	void updateScale(int browserWidth, int browserHeight){
		scaleAttributes.scaleX = static_cast<double>(browserWidth) / static_cast<double>(scaleAttributes.NATIVE_WIDTH);
		scaleAttributes.scaleY = static_cast<double>(browserHeight) / static_cast<double>(scaleAttributes.NATIVE_HEIGHT);

		if(scaleAttributes.currentAspectRatio > scaleAttributes.nativeAspectRatio){
			scaleAttributes.scaleY = scaleAttributes.scaleX;
		}
		else if(scaleAttributes.currentAspectRatio < scaleAttributes.nativeAspectRatio){
			scaleAttributes.scaleX = scaleAttributes.scaleY;
		}

		scaleAttributes.scaledWidth = round(browserWidth / scaleAttributes.scaleX);
		scaleAttributes.scaledHeight = round(browserHeight / scaleAttributes.scaleY);
	}

	void applyScale(Layer layer){
		scale(layer, scaleAttributes.devicePixelRatio, scaleAttributes.devicePixelRatio);
		scale(layer, scaleAttributes.scaleX, scaleAttributes.scaleY);
	}

	void scale(Layer layer, double scaleX, double scaleY){
		EM_ASM({
			contexts[$0].scale($1, $2);
		}, layer, scaleX, scaleY);
	}

	void setTransform(Layer layer, double hScale, double hSkew, double vSkew, double vScale, double hMove, double vMove){
		EM_ASM({
			contexts[$0].setTransform($1, $2, $3, $4, $5, $6);
		}, layer, hScale, hSkew, vSkew, vScale, hMove, vMove);
	}

	void drawLine(Layer layer, int x1, int y1, int x2, int y2){
		beginPath(layer);
		moveTo(layer, x1, y1);
		lineTo(layer, x2, y2);
		stroke(layer);
	}

	void beginPath(Layer layer){
		EM_ASM_({
			contexts[$0].beginPath();
		}, layer);
	}

	void arc(Layer layer, int x, int y, int radius, double startAngleRadians, double endAngleRadians){
		if(radius < 1){
			return;
		}
		EM_ASM_({
			contexts[$0].arc($1, $2, $3, $4, $5);
		}, layer, x, y, radius, startAngleRadians, endAngleRadians);
	}

	void moveTo(Layer layer, double x, double y){
		EM_ASM_({
			contexts[$0].moveTo($1, $2);
		}, layer, x, y);
	}

	void lineTo(Layer layer, double x, double y){
		EM_ASM_({
			contexts[$0].lineTo($1, $2);
		}, layer, x, y);
	}

	void fill(Layer layer){
		EM_ASM_({
			contexts[$0].fill();
		}, layer);
	}

	void stroke(Layer layer){
		EM_ASM_({
			contexts[$0].stroke();
		}, layer);
	}

	void setLineWidth(Layer layer, int lineWidth){
		EM_ASM_({
			contexts[$0].lineWidth = $1;
		}, layer, lineWidth);
	}

	void strokeRect(Layer layer, int x, int y, int width, int height){
		EM_ASM_({
			contexts[$0].strokeRect($1, $2, $3, $4);
		}, layer, x, y, width, height);
	}

	void fillRect(Layer layer, int x, int y, int width, int height){
		EM_ASM_({
			contexts[$0].fillRect($1, $2, $3, $4);
		}, layer, x, y, width, height);
	}

	void setStrokeStyle(Layer layer, int r, int g, int b){
		EM_ASM_({
			contexts[$0].strokeStyle = "rgb(" + $1 + ", " + $2 + ", " + $3 + ")";
		}, layer, r, g, b);
	}

	void setFillStyle(Layer layer, int r, int g, int b){
		EM_ASM_({
			contexts[$0].fillStyle = "rgb(" + $1 + ", " + $2 + ", " + $3 + ")";
		}, layer, r, g, b);
	}

	void setGlobalAlpha(Layer layer, double globalAlpha){
		if(globalAlpha < 0){
			globalAlpha = 0;
		}
		EM_ASM_({
			contexts[$0].globalAlpha = $1;
		}, layer, globalAlpha);
	}

	void setTextAlign(Layer layer, std::string alignment){
		EM_ASM_({
			contexts[$0].textAlign = UTF8ToString($1);
		}, layer, alignment.c_str());
	}

	void setTextBaseline(Layer layer, std::string textBaseline){
		EM_ASM_({
			contexts[$0].textBaseline = UTF8ToString($1);
		}, layer, textBaseline.c_str());
	}

	void setFontSize(Layer layer, int fontSize){
		EM_ASM_({
			contexts[$0].font = $1 + "px 'Arial', sans-serif";
		}, layer, fontSize);
	}

	void fillText(Layer layer, std::string text, int x, int y){
		EM_ASM_({
			contexts[$0].fillText(UTF8ToString($1), $2, $3);
		}, layer, text.c_str(), x, y);
	}

	void strokeText(Layer layer, std::string text, int x, int y){
		EM_ASM_({
			contexts[$0].strokeText(UTF8ToString($1), $2, $3);
		}, layer, text.c_str(), x, y);
	}
}