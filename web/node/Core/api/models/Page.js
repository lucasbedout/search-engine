/**
 * Page
 *
 * @module      :: Model
 * @description :: A short summary of how this model works and what it represents.
 * @docs		:: http://sailsjs.org/#!documentation/models
 */

module.exports = {
  tableName: 'pages',
  attributes: {

      title: {
          type: 'string',
          required: true
      },
      url: {
          type: 'string',
          required: true
      },
      keywords: {
          type: 'string',
          required: true
      },
      description: {
          type: 'text',
          required: true
      },
      content: {
          type: 'text'
      }
  }

};
