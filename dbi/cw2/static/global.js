// Send an AJAX request
function ajax( url, done, json ) {
  var req = new XMLHttpRequest();
  req.open( 'GET', url, true );
  req.send();

  req.onreadystatechange = function() {
    if ( req.readyState != XMLHttpRequest.DONE || req.status == 500 ) {
      return;
    }

    try {
      done( json? JSON.parse( req.responseText ) : req.responseText, req );
    } catch ( e ) {
      window.location = url;
    }
  }

  return req;
}

// Load local links through AJAX
var BASEURL, headerAs = [], currA;
function ajaxLoad( url, elem = null ) {

  ajax( url +'?ajax', function( res ) {
    // Highlight correct header link
    if ( currA ) currA.classList.remove( 'current' );
    var newA = headerAs[url];
    if ( newA ) {
      newA.classList.add( 'current' );
      currA = newA;
    }

    document.title = res.title !== 'Songbase'? res.title+' | Songbase' : 'Songbase';
    var content = document.getElementsByTagName( 'center' )[0];
    if ( res.html != '' ) {
      content.innerHTML = res.html;
      parseContent( content );
    }

    window.history.pushState( { html: content.innerHTML, pageTitle: document.title },
      "", url );

  }, true );

}

// Form validation
function validate( form ) {

  form.onsubmit = function( e ) {
    // Erroring element / error message
    var elem, msg;

    // Loop through form elements, for each label validate its input element
    for ( var label of this.getElementsByTagName( 'label' ) ) {
      var elem   = label.children[0],
        val      = elem.value,
        required = elem.required,
        patt     = elem.pattern,
        min      = elem.min,
        maxlen   = elem.maxLength;

        console.log( required, patt, min, maxlen );

      // Perform validation on each attribute
      if ( required && ( val === '' ||
        elem.tagName == 'SELECT' && elem.selectedIndex == 0 )
      ) {
        // Required but blank, or a disabled option is still selected for drop-downs
        msg = `'${elem.name}' must not be blank`;
        break;

      } else if ( patt && !val.match( patt ) ) {
        // Does not match given pattern
        msg = `'${elem.name}' must not be blank`;
        break;

      } else if ( maxlen > 0 && val.length > maxlen ) {
        // Greater than max length
        msg = `'${elem.name}' length must be less than ${maxlen}`;
        break;

      } else if ( min && val < min ) {
        // Less than minimum
        msg = `'${elem.name}' must be at least ${min}`;
        break;
      }
      // Remove invalid class in case it had previously been applied
      elem.classList.remove( 'invalid' );
    }

    // msg not being null indicates validation error
    if ( msg ) {
      // Add invalid class, output error message, prevent submission
      elem.classList.add( 'invalid' );
      alert( msg );
      return false;
    }

    return true;
  }
}

// Manage the contents when it is reloaded
function parseContent( html ) {

  for ( var elem of html.getElementsByTagName( 'a' ) ) {
    if ( !elem.href.startsWith( BASEURL ) ) continue;

    elem.onclick = function( e ) {
      if ( this.href == window.location ) {
        e.preventDefault();
        return false;
      }

      ajaxLoad( this.href, this );
      e.preventDefault();
      return false;
    }
  }

  for ( var elem of html.getElementsByTagName( 'form' ) ) {
    validate( elem );
  }
}

window.onload = function() {

  // Store base path so we can check if links are local stackoverflow.com/a/6167979
  BASEURL = location.origin || location.protocol + '//' + location.host

  // Store header links, identify active one
  var header = document.getElementsByTagName( 'header' )[0];
  for ( a of header.getElementsByTagName( 'a' ) ) headerAs[ a.href ] = a;
  currA = header.getElementsByClassName( 'current' )[0];

  // Parse entire document to find links and forms
  parseContent( document.body );
}

// Replace contents when user goes back in history
window.onpopstate = function( e ) {
  var state = history.state;
  document.title = state.pageTitle;
  var content = document.getElementsByTagName( 'center' )[0];
  content.innerHTML = state.html;
  parseContent( content );
}
