void otsu_th( )
	/* binarization by Otsu's method 
	   based on maximization of inter-class variance */

{
	int hist[GRAYLEVEL];
	double prob[GRAYLEVEL], omega[GRAYLEVEL]; /* prob of graylevels */
	double myu[GRAYLEVEL];   /* mean value for separation */
	double max_sigma, sigma[GRAYLEVEL]; /* inter-class variance */
	int i, x, y; /* Loop variable */
	int threshold; /* threshold for binarization */

	printf("Otsu's binarization process starts now.\n");

	/* Histogram generation */
	for (i = 0; i < GRAYLEVEL; i++) hist[i] = 0;
	for (y = 0; y < y_size1; y++)
		for (x = 0; x < x_size1; x++) {
			hist[image1[y][x]]++;
		}
	/* calculation of probability density */
	for ( i = 0; i < GRAYLEVEL; i ++ ) {
		prob[i] = (double)hist[i] / (x_size1 * y_size1);
	}

	/* omega & myu generation */
	omega[0] = prob[0];
	myu[0] = 0.0;       /* 0.0 times prob[0] equals zero */
	for (i = 1; i < GRAYLEVEL; i++) {
		omega[i] = omega[i-1] + prob[i];
		myu[i] = myu[i-1] + i*prob[i];
	}

	/* sigma maximization
	   sigma stands for inter-class variance 
	   and determines optimal threshold value */
	threshold = 0;
	max_sigma = 0.0;
	for (i = 0; i < GRAYLEVEL-1; i++) {
		if (omega[i] != 0.0 && omega[i] != 1.0)
			sigma[i] = pow(myu[GRAYLEVEL-1]*omega[i] - myu[i], 2) / 
				(omega[i]*(1.0 - omega[i]));
		else
			sigma[i] = 0.0;
		if (sigma[i] > max_sigma) {
			max_sigma = sigma[i];
			threshold = i;
		}
	}

	printf("\nthreshold value = %d\n", threshold);

	/* binarization output into image2 */
	x_size2 = x_size1;
	y_size2 = y_size1;
	for (y = 0; y < y_size2; y++)
		for (x = 0; x < x_size2; x++)
			if (image1[y][x] > threshold)
				image2[y][x] = MAX_BRIGHTNESS;
			else
				image2[y][x] = 0;

}




