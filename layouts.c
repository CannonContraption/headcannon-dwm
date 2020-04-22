/*
  Centered Master - Like tile, but master in the center

  From the DWM patch library- Centered Master
 */
void centeredmaster(
    Monitor * monitor)
{
  unsigned int i, n, h, mw, mx, my, oty, ety, tw;
  Client *c;

  /* count number of clients in the selected monitor */
  for (n = 0, c = nexttiled(monitor->clients); c; c = nexttiled(c->next), n++);
  if(n == 0)
    return;

  /* initialize areas */
  mw = monitor->ww;
  mx = 0;
  my = 0;
  tw = mw;

  if (n > monitor->nmaster){
    /* go mfact box in the center if more than nmaster clients */
    mw = monitor->nmaster ? monitor->ww * monitor->mfact : 0;
    tw = monitor->ww - mw;

    if (n - monitor->nmaster > 1) {
      /* only one client */
      mx = (monitor->ww - mw) / 2;
      tw = (monitor->ww - mw) / 2;
    }
  }

  oty = 0;
  ety = 0;
  for (i = 0, c = nexttiled(monitor->clients); c; c = nexttiled(c->next), i++)
    if (i < monitor->nmaster) {
      /* nmaster clients are stacked vertically, in the center
       * of the screen */
      h = (monitor->wh - my) / (MIN(n, monitor->nmaster) - i);
      resize(c, monitor->wx + mx, monitor->wy + my, mw - (2*c->bw),
             h - (2*c->bw), 0);
      my += HEIGHT(c);
    } else {
      /* stack clients are stacked vertically */
      if ((i - monitor->nmaster) % 2 ) {
        h = (monitor->wh - ety) / ( (1 + n - i) / 2);
        resize(c, monitor->wx, monitor->wy + ety, tw - (2*c->bw),
               h - (2*c->bw), 0);
        ety += HEIGHT(c);
      } else {
        h = (monitor->wh - oty) / ((1 + n - i) / 2);
        resize(c, monitor->wx + mx + mw, monitor->wy + oty,
               tw - (2*c->bw), h - (2*c->bw), 0);
        oty += HEIGHT(c);
      }
    }
}

/*
  gaplessgrid - Grid layout
 */
void gaplessgrid(
    Monitor * monitor)
{
  unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch;
  Client *c;

  for(n = 0, c = nexttiled(monitor->clients); c; c = nexttiled(c->next))
    n++;
  if(n == 0)
    return;

  /* grid dimensions */
  for(cols = 0; cols <= n/2; cols++)
    if(cols*cols >= n)
      break;

  rows = n/cols;

  /* window geometries */
  cw = cols ? monitor->ww / cols : monitor->ww;
  cn = 0; /* current column number */
  rn = 0; /* current row number */
  for(i = 0, c = nexttiled(monitor->clients); c; i++, c = nexttiled(c->next)) {
    if(i/rows + 1 > cols - n%cols)
      rows = n/cols + 1;
    ch = rows ? monitor->wh / rows : monitor->wh;
    cx = monitor->wx + cn*cw;
    cy = monitor->wy + rn*ch;
    resize(c, cx, cy, cw - 2 * c->bw, ch - 2 * c->bw, False);
    rn++;
    if(rn >= rows) {
      rn = 0;
      cn++;
    }
  }
}

/*
  Monocle - Lay out windows in a single stack

  Monocle layout from upstream DWM- shows one window full-screen at a time
 */
void monocle(
    Monitor * monitor)
{
	unsigned int n = 0;
	Client *c;

	for (c = monitor->clients; c; c = c->next)
		if (ISVISIBLE(c))
			n++;
	if (n > 0) /* override layout symbol */
		snprintf(monitor->ltsymbol, sizeof monitor->ltsymbol, "[%d]", n);
	for (c = nexttiled(monitor->clients); c; c = nexttiled(c->next))
		resize(c, monitor->wx, monitor->wy, monitor->ww - 2 * c->bw, monitor->wh - 2 * c->bw, 0);
}

/*
  Tile - The TILED layout (upstream DWM default)

  Lays out windows in a stack, with a single master window
 */
void tile(
    Monitor * monitor)
{
  unsigned int i, n, h, mw, my, ty;
  Client *c;

  for (n = 0, c = nexttiled(monitor->clients); c; c = nexttiled(c->next), n++);
  if (n == 0)
    return;

  if (n > monitor->nmaster)
    mw = monitor->nmaster ? monitor->ww * monitor->mfact : 0;
  else
    mw = monitor->ww;
  for (i = my = ty = 0, c = nexttiled(monitor->clients); c; c = nexttiled(c->next), i++)
    if (i < monitor->nmaster) {
      h = (monitor->wh - my) / (MIN(n, monitor->nmaster) - i);
      resize(c, monitor->wx, monitor->wy + my, mw - (2*c->bw), h - (2*c->bw), 0);
      my += HEIGHT(c);
    } else {
      h = (monitor->wh - ty) / (n - i);
      resize(c, monitor->wx + mw, monitor->wy + ty, monitor->ww - mw - (2*c->bw), h - (2*c->bw), 0);
      ty += HEIGHT(c);
    }
}

/*
  tricolumn - Three column text editing layout

  Puts windows in three columns for editing source code
 */
void tricolumn(
    Monitor *monitor)
{
  unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch;
  Client *c;

  for(n = 0, c = nexttiled(monitor->clients); c; c = nexttiled(c->next))
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
  cw = cols ? monitor->ww / cols : monitor->ww;
  cn = 0; /* current column number */
  rn = 0; /* current row number */
  for(i = 0, c = nexttiled(monitor->clients); c; i++, c = nexttiled(c->next)) {
    if(i/rows + 1 > cols - n%cols)
      rows = n/cols + 1;
    ch = rows ? monitor->wh / rows : monitor->wh;
    cx = monitor->wx + cn*cw;
    cy = monitor->wy + rn*ch;
    resize(c, cx, cy, cw - 2 * c->bw, ch - 2 * c->bw, False);
    rn++;
    if(rn >= rows) {
      rn = 0;
      cn++;
    }
  }
        
}
