static int diff_no_prefix;
static size_t fill_textconv(struct userdiff_driver *driver,
			    struct diff_filespec *df, char **outbuf);
	if (!strcmp(var, "diff.noprefix")) {
		diff_no_prefix = git_config_bool(var, value);
		return 0;
	}
			      struct userdiff_driver *textconv_one,
			      struct userdiff_driver *textconv_two,
	char *data_one, *data_two;
	size_one = fill_textconv(textconv_one, one, &data_one);
	size_two = fill_textconv(textconv_two, two, &data_two);
struct diff_words_style_elem
{
	const char *prefix;
	const char *suffix;
	const char *color; /* NULL; filled in by the setup code if
			    * color is enabled */
};

struct diff_words_style
{
	enum diff_words_type type;
	struct diff_words_style_elem new, old, ctx;
	const char *newline;
};

struct diff_words_style diff_words_styles[] = {
	{ DIFF_WORDS_PORCELAIN, {"+", "\n"}, {"-", "\n"}, {" ", "\n"}, "~\n" },
	{ DIFF_WORDS_PLAIN, {"{+", "+}"}, {"[-", "-]"}, {"", ""}, "\n" },
	{ DIFF_WORDS_COLOR, {"", ""}, {"", ""}, {"", ""}, "\n" }
};

	enum diff_words_type type;
	struct diff_words_style *style;
static int fn_out_diff_words_write_helper(FILE *fp,
					  struct diff_words_style_elem *st_el,
					  const char *newline,
					  size_t count, const char *buf)
{
	while (count) {
		char *p = memchr(buf, '\n', count);
		if (p != buf) {
			if (st_el->color && fputs(st_el->color, fp) < 0)
				return -1;
			if (fputs(st_el->prefix, fp) < 0 ||
			    fwrite(buf, p ? p - buf : count, 1, fp) != 1 ||
			    fputs(st_el->suffix, fp) < 0)
				return -1;
			if (st_el->color && *st_el->color
			    && fputs(GIT_COLOR_RESET, fp) < 0)
				return -1;
		}
		if (!p)
			return 0;
		if (fputs(newline, fp) < 0)
			return -1;
		count -= p + 1 - buf;
		buf = p + 1;
	}
	return 0;
}

	struct diff_words_style *style = diff_words->style;
		fn_out_diff_words_write_helper(diff_words->file,
				&style->ctx, style->newline,
				plus_begin - diff_words->current_plus,
				diff_words->current_plus);
		fn_out_diff_words_write_helper(diff_words->file,
				&style->old, style->newline,
		fn_out_diff_words_write_helper(diff_words->file,
				&style->new, style->newline,
	struct diff_words_style *style = diff_words->style;
		fn_out_diff_words_write_helper(diff_words->file,
			&style->old, style->newline,
	xpp.flags = 0;
		fn_out_diff_words_write_helper(diff_words->file,
			&style->ctx, style->newline,
			- diff_words->current_plus, diff_words->current_plus);
		if (ecbdata->diff_words
		    && ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN)
			fputs("~\n", ecbdata->file);
		if (ecbdata->diff_words->type == DIFF_WORDS_PORCELAIN) {
			emit_line(ecbdata->file, plain, reset, line, len);
			fputs("~\n", ecbdata->file);
		} else {
			/* don't print the prefix character */
			emit_line(ecbdata->file, plain, reset, line+1, len-1);
		}
static struct userdiff_driver *get_textconv(struct diff_filespec *one)
	if (!one->driver->textconv)
		return NULL;

	if (one->driver->textconv_want_cache && !one->driver->textconv_cache) {
		struct notes_cache *c = xmalloc(sizeof(*c));
		struct strbuf name = STRBUF_INIT;

		strbuf_addf(&name, "textconv/%s", one->driver->name);
		notes_cache_init(c, name.buf, one->driver->textconv);
		one->driver->textconv_cache = c;
	}

	return one->driver;
	struct userdiff_driver *textconv_one = NULL;
	struct userdiff_driver *textconv_two = NULL;
		if (xfrm_msg)
			strbuf_addstr(&header, xfrm_msg);
		if (xfrm_msg)
			strbuf_addstr(&header, xfrm_msg);
		if (xfrm_msg)
			strbuf_addstr(&header, xfrm_msg);
	    ( (!textconv_one && diff_filespec_is_binary(one)) ||
	      (!textconv_two && diff_filespec_is_binary(two)) )) {
		if (fill_mmfile(&mf1, one) < 0 || fill_mmfile(&mf2, two) < 0)
			die("unable to read files to diff");
		mf1.size = fill_textconv(textconv_one, one, &mf1.ptr);
		mf2.size = fill_textconv(textconv_two, two, &mf2.ptr);
		xpp.flags = o->xdl_opts;
		if (o->word_diff) {
			int i;

			ecbdata.diff_words->type = o->word_diff;
			for (i = 0; i < ARRAY_SIZE(diff_words_styles); i++) {
				if (o->word_diff == diff_words_styles[i].type) {
					ecbdata.diff_words->style =
						&diff_words_styles[i];
					break;
				}
			}
			if (DIFF_OPT_TST(o, COLOR_DIFF)) {
				struct diff_words_style *st = ecbdata.diff_words->style;
				st->old.color = diff_get_color_opt(o, DIFF_FILE_OLD);
				st->new.color = diff_get_color_opt(o, DIFF_FILE_NEW);
				st->ctx.color = diff_get_color_opt(o, DIFF_PLAIN);
			}
		if (o->word_diff)
		xpp.flags = o->xdl_opts;
		xpp.flags = 0;
			  struct diff_filepair *p,
			  int use_color)
	const char *set = diff_get_color(use_color, DIFF_METAINFO);
	const char *reset = diff_get_color(use_color, DIFF_RESET);

		strbuf_addf(msg, "%ssimilarity index %d%%",
			    set, similarity_index(p));
		strbuf_addf(msg, "%s\n%scopy from ", reset, set);
		strbuf_addf(msg, "%s\n%scopy to ", reset, set);
		strbuf_addf(msg, "%s\n", reset);
		strbuf_addf(msg, "%ssimilarity index %d%%",
			    set, similarity_index(p));
		strbuf_addf(msg, "%s\n%srename from ", reset, set);
		strbuf_addf(msg, "%s\n%srename to ", reset, set);
		strbuf_addf(msg, "%s\n", reset);
			strbuf_addf(msg, "%sdissimilarity index %d%%%s\n",
				    set, similarity_index(p), reset);
		strbuf_addf(msg, "%sindex %s..", set,
			    find_unique_abbrev(one->sha1, abbrev));
		strbuf_addstr(msg, find_unique_abbrev(two->sha1, abbrev));
		strbuf_addf(msg, "%s\n", reset);
	if (msg) {
		/*
		 * don't use colors when the header is intended for an
		 * external diff driver
		 */
		fill_metainfo(msg, name, other, one, two, o, p,
			      DIFF_OPT_TST(o, COLOR_DIFF) && !pgm);
		xfrm_msg = msg->len ? msg->buf : NULL;
	}

	memset(&diff_queued_diff, 0, sizeof(diff_queued_diff));
	if (diff_no_prefix) {
		options->a_prefix = options->b_prefix = "";
	} else if (!diff_mnemonic_prefix) {
	if (!strcmp(arg, "-p") || !strcmp(arg, "-u") || !strcmp(arg, "--patch"))
		options->word_diff = DIFF_WORDS_COLOR;
		options->word_diff = DIFF_WORDS_COLOR;
	else if (!strcmp(arg, "--word-diff")) {
		if (options->word_diff == DIFF_WORDS_NONE)
			options->word_diff = DIFF_WORDS_PLAIN;
	}
	else if (!prefixcmp(arg, "--word-diff=")) {
		const char *type = arg + 12;
		if (!strcmp(type, "plain"))
			options->word_diff = DIFF_WORDS_PLAIN;
		else if (!strcmp(type, "color")) {
			DIFF_OPT_SET(options, COLOR_DIFF);
			options->word_diff = DIFF_WORDS_COLOR;
		}
		else if (!strcmp(type, "porcelain"))
			options->word_diff = DIFF_WORDS_PORCELAIN;
		else if (!strcmp(type, "none"))
			options->word_diff = DIFF_WORDS_NONE;
		else
			die("bad --word-diff argument: %s", type);
	}
	else if (!prefixcmp(arg, "--word-diff-regex=")) {
		if (options->word_diff == DIFF_WORDS_NONE)
			options->word_diff = DIFF_WORDS_PLAIN;
		options->word_regex = arg + 18;
	}
		xpp.flags = 0;
	DIFF_QUEUE_CLEAR(q);
	DIFF_QUEUE_CLEAR(q);
	DIFF_QUEUE_CLEAR(&outq);
	DIFF_QUEUE_CLEAR(&outq);
	/* We never run this function more than one time, because the
	 * rename/copy detection logic can only run once.
	 */
	if (diff_queued_diff.run)
		return;


	diff_queued_diff.run = 1;

static size_t fill_textconv(struct userdiff_driver *driver,
			    struct diff_filespec *df,
			    char **outbuf)
{
	size_t size;

	if (!driver || !driver->textconv) {
		if (!DIFF_FILE_VALID(df)) {
			*outbuf = "";
			return 0;
		}
		if (diff_populate_filespec(df, 0))
			die("unable to read files to diff");
		*outbuf = df->data;
		return df->size;
	}

	if (driver->textconv_cache) {
		*outbuf = notes_cache_get(driver->textconv_cache, df->sha1,
					  &size);
		if (*outbuf)
			return size;
	}

	*outbuf = run_textconv(driver->textconv, df, &size);
	if (!*outbuf)
		die("unable to read files to diff");

	if (driver->textconv_cache) {
		/* ignore errors, as we might be in a readonly repository */
		notes_cache_put(driver->textconv_cache, df->sha1, *outbuf,
				size);
		/*
		 * we could save up changes and flush them all at the end,
		 * but we would need an extra call after all diffing is done.
		 * Since generating a cache entry is the slow path anyway,
		 * this extra overhead probably isn't a big deal.
		 */
		notes_cache_write(driver->textconv_cache);
	}

	return size;
}