/*!
 * u.js - Version 0.14.0 - IE 9 fix
 * Fix for the missing classList in IE 9
 * Author: Steve Ottoz <so@dev.so>
 * Build date: 2015-07-16
 * Copyright (c) 2015 Steve Ottoz
 * Released under the MIT license
 */
(function(u,window,document) {
  'use strict';


  /**
   * wait for body to be available
   * insert function call at beginning of list to execute it before any other registered function
   */
  u(function () {


    /**
     * overwrite class methods if classList is not defined
     */
    if (!document.body.classList) {


      /**
       * hasClass method
       * check if element has class
       * @param  {string}  cls - class name to check for
       * @return {boolean}
       */
      u.fn.hasClass = function(cls) {
        return new RegExp('(^| )' + cls + '( |$)', 'gi').test(this[0].className);
      };


      /**
       * addClass method
       * @param  {string} cls  - class name
       * @return {object} this
       */
      u.fn.addClass = function(cls) {
        return this.each(function(i, el) {
          el.className += ' ' + cls;
        });
      };


      /**
       * removeClass method
       * @param  {string} cls  - class name
       * @return {object} this
       */
      u.fn.removeClass = function(cls) {
        return this.each(function(i, el) {
          el.className = el.className.replace(new RegExp('(^|\\b)' + cls.split(' ').join('|') + '(\\b|$)', 'gi'), ' ');
        });
      };


      /**
       * toggleClass method
       * @param  {string} cls  - class name
       * @return {object} this
       */
      u.fn.toggleClass = function(cls) {
        return this.each(function(i, el) {
          var classes = el.className.split(' '),
              existingIndex = classes.indexOf(cls);

          if (existingIndex >= 0) {
            classes.splice(existingIndex, 1);
          }
          else {
            classes.push(cls);
          }

          el.className = classes.join(' ');
        });
      };

    }


  });


})(u,window,document);
