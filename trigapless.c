void
trigaplessgrid(Monitor *m) {
	unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next))
		n++;
	if(n == 0)
		return;

        cols=3;
        if (cols > n)
          {
            cols = n;
          }
        rows=n/cols;

	/* window geometries */
	cw = cols ? m->ww / cols : m->ww;
	cn = 0; /* current column number */
	rn = 0; /* current row number */
        for(i = 0, c = nexttiled(m->clients); c; i++, c = nexttiled(c->next)) {
		if(i/rows + 1 > cols - n%cols)
			rows = n/cols + 1;
		ch = rows ? m->wh / rows : m->wh;
		cx = m->wx + cn*cw;
		cy = m->wy + rn*ch;
		resize(c, cx, cy, cw - 2 * c->bw, ch - 2 * c->bw, False);
		rn++;
		if(rn >= rows) {
			rn = 0;
			cn++;
		}
	}
        
}