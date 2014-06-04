/**
 * Search
 *
 * @module      :: Model
 * @description :: A short summary of how this model works and what it represents.
 * @docs		:: http://sailsjs.org/#!documentation/models
 */

module.exports = {

  attributes: {

      keywords: {
          type: 'string',
          required: true
      },
      result: {
          type: 'text',
          required: true
      },
      time: {
          type: 'float',
          required: true
      }
  }
};
