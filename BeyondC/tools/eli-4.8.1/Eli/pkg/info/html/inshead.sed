# $Id: inshead.sed,v 1.2 2008/03/22 11:55:32 profw Exp $

/%HEAD%/{
r HEAD.html
d
}
/%FOOT%/{
r FOOT.html
d
}
p
