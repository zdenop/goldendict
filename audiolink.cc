/* This file is (c) 2008-2012 Konstantin Isakov <ikm@goldendict.org>
 * Part of GoldenDict. Licensed under GPLv3 or later, see the LICENSE file */

#include "audiolink.hh"

std::string addAudioLink( std::string const & url,
                          std::string const & dictionaryId )
{
    return std::string( "<script language=\"JavaScript\">" +
                        makeAudioLinkScript( url, dictionaryId ) +
                        "</script>" );
}

std::string makeAudioLinkScript( std::string const & url,
                                 std::string const & dictionaryId )
{
  /// Convert "'" to "\'" - this char broke autoplay of audiolinks

  std::string ref;
  bool escaped = false;
  for( unsigned x = 0; x < url.size(); x++ )
  {
    char ch = url[ x ];
    if( escaped )
    {
      ref += ch;
      escaped = false;
      continue;
    }
    if( ch == '\'' )
      ref += '\\';
    ref += ch;
    escaped = ( ch == '\\' );
  }

  return std::string( "var gdAudioLink; "
                      "if ( !gdAudioLink ) gdAudioLink=" ) + ref +
         "; if ( typeof gdActivateAudioLink_" + dictionaryId + " != 'function' ) {"
         "eval( 'function gdActivateAudioLink_" + dictionaryId + "() {"
         "gdAudioLink=" + ref + "; }' ); }";
}
