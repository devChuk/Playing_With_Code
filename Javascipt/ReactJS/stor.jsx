define( function (require) {

  var TermsView = require('js/com.betterpath/views/Terms');

  var CssMixin = require('rendered/react/mixins/CssMixin'),
      OldSiteMixin = require('rendered/react/mixins/OldSiteMixin'),
      PageMixin = require('rendered/react/mixins/PageMixin');
  
  var Api = require('api');

  /*
  Here's the hierarchy
  TermsOld
    EditableTerms
      Summary[]
        SummarySection[]
  */

  var SummarySection = React.createClass({
    propTypes: {
      removeTerm: React.PropTypes.func,
      updateTerms: React.PropTypes.func,
      section: React.PropTypes.string,
      deletable: React.PropTypes.bool,
      item: React.PropTypes.object,
      key: React.PropTypes.number,
      reactKey: React.PropTypes.number
    },

    getInitialState: function() {
      return {
        title: this.props.item.title,
        description: this.props.item.description,
        deletable: this.props.deletable
      };
    },

    handleTitleChange: function(event) {
      this.setState({
        title: event.target.value
      });
    },

    handleDescriptChange: function(event) {
      this.setState({
        description: event.target.value
      });
    },

    handleRemove: function() {
      this.props.removeTerm(this.props.reactKey);
    },

    handleUnfocus: function() {
      var filled = this.state.title.length > 0;
        if (filled) {
          this.setState({deletable: true});
        }
        this.props.updateTerms(this.props.reactKey, this.state.title.length > 0, this.state.title, this.state.description);
    },

    render: function() {
      var titleName = "data["+this.props.section+"][][title]";
      var descName = "data["+this.props.section+"][][description]";
      var deletable;

      if (this.state.deletable) {
        deletable = (
          <section className="inline-block term-remove">
            <div className="btnRemove inline-block" onClick={this.handleRemove}></div>
          </section>
        );
      }

      return (
        <div className="term-row">
          {deletable}
          <input value={this.state.title} onBlur={this.handleUnfocus} onChange={this.handleTitleChange} type="text" name={titleName} className="form-control longInput term-title" />
          <textarea value={this.state.description} onBlur={this.handleUnfocus} onChange={this.handleDescriptChange} name={descName} type="text" rows="3" className="inputTextNormal longInput term-description form-control"></textarea>
        </div>
      );
    }
  });

  var Summary = React.createClass({
    propTypes: {
      name: React.PropTypes.string,
      section: React.PropTypes.string,
      data: React.PropTypes.array
    },

    getInitialState: function() {
      return {
        terms: [],
        refresh: true
      }
    },

    removeTerm: function(reactKey) {
      var terms = this.state.terms;
      terms[reactKey] = {
        html: null,
        deletable: true
      };

      this.setState({
        terms: terms
      });

      this.props.updateformData(this.props.section, terms);
    },

    updateTerms: function(reactKey, bool, title, description) {
      var terms = this.state.terms;
      terms[reactKey].deletable = bool;
      terms[reactKey].title = title;
      terms[reactKey].description = description;
      var needsNewSummarySection = true;
      var emptySummarySection = {
        title: "",
        description: ""
      };

      for (var i = 0; i < terms.length; i++) {
        if (!(terms[i].deletable)) {
          needsNewSummarySection = false;
          break;
        }
      }

      if (needsNewSummarySection) {
        terms.push({
          html: (<SummarySection removeTerm={this.removeTerm} updateTerms={this.updateTerms} section={this.props.section} deletable={false} item={emptySummarySection} key={terms.length} reactKey={terms.length}/>),
          deletable: false,
          title: null,
          description: null
        });
      }

      this.setState({
        terms: terms
      });

      this.props.updateformData(this.props.section, terms);
    },

    componentWillReceiveProps: function (newProps) {
      var terms = [];
      var emptySummarySection = {
        title: "",
        description: ""
      };

      if (newProps.data && this.state.refresh) {

        for (var i = 0; i < newProps.data.length; i++) {
          var html = (<SummarySection removeTerm={this.removeTerm} updateTerms={this.updateTerms} section={this.props.section} deletable={true} item={newProps.data[i]} key={i} reactKey={i}/>);
          terms.push({
            html: html,
            deletable: true,
            title: newProps.data[i].title,
            description: newProps.data[i].description
          });
        }

        terms.push({
          html:(<SummarySection removeTerm={this.removeTerm} updateTerms={this.updateTerms} section={this.props.section} deletable={false} item={emptySummarySection} key={terms.length} reactKey={terms.length}/>),
          deletable: false,
          title: null,
          description: null
        });

        this.setState({
          refresh: false,
          terms: terms
        });
        this.props.updateformData(this.props.section, terms);
      }
    },

    render: function() {
      var id = '';
      if (this.props.section == 'fullSummary') {
        id = 'terms-full-summary';
      }
      else {
        id= 'terms-change-summary';
      }
      var rows = [];
      for (var i = 0; i < this.state.terms.length; i++) {
        rows.push(this.state.terms[i].html);
      }

      return (
        <div className="term-section">
          <label className="oversized-label inset">{this.props.name}</label>
          <div id={id}>
            {rows}
          </div>
        </div>
      );
    }
  });

  var EditableTerms = React.createClass({
    mixins: [CssMixin, PageMixin],

    getInitialState: function() {
      return {
        oldCss: true,
        version: "",
        date: "",
        data: {},
        fullSummary: {},
        changeSummary: {}
      }
    },

    updateformData: function(summary, data) {
      var formattedData = [];
      for (var i = 0; i < data.length; i++) {
        if (data[i].deletable && data[i].title) {
          formattedData.push({
            title: data[i].title,
            description: data[i].description
          });
        }
      }

      if (summary == "fullSummary") {
        this.setState({
          fullSummary: formattedData
        });
      }
      else if (summary == "changeSummary") {
        this.setState({
          changeSummary: formattedData
        });
      }
    },

    handleVerChange: function(event) {
      this.setState({
        version: event.target.value
      });
    },

    handleDateChange: function(event) {
      this.setState({
        date: event.target.value
      });
    },

    success: function() {
      window.location.replace('/');
    },

    save: function() {
      event.preventDefault();

      var data = {
        date: this.state.date,
        fullSummary: this.state.fullSummary,
        changeSummary: this.state.changeSummary
      }
      var stringData = JSON.stringify(data);
      var formData = {
        version: this.state.version,
        data: stringData
      }

      var route = new Api.Route('UPDATE', 'terms', {}, {});
      var request = new Api.Call(route, formData);

      var _this = this;
      request.on(Api.Status.SUCCESS, function(res) {
        _this.success();
      });
      request.execute();
    },

    componentDidMount: function () {
      var _this = this;

      var setState = this.setState.bind(this);

      var route = new Api.Route('SHOW', 'terms', {}, {});
      var request = new Api.Call(route);
      request.on(Api.Status.SUCCESS, function(res) {
        var data = JSON.parse(res.data.data);
        var version = res.data.version;
        var date = data.date;

        setState({
          version: version,
          date: date,
          data: data
        });
      });
      request.execute();
    },

    render: function() {
      return (
        <div id="mainBody" className="container">
          <div className="mainContentFull basicPage">
            <div id="header" className="panel-heading heading-normal content-side-padding container fixed-header">
              <h2 id="pageTitle" className="inline-block vcenter"><span>Terms of Service</span></h2>
            </div>
            <div style={{paddingTop: 50 + 'px'}}>
              <form id="form-terms" className="contentPadding">
                <div>
                    <div className="terms-left">
                      <label className="oversized-label inset">Version</label>
                      <div>
                        <input type="text" name="version" maxLength="5" size="8" value={this.state.version} onChange={this.handleVerChange} className="form-control terms-version" />
                      </div>
                    </div>
                  <div className="terms-left">
                    <label className="oversized-label inset">Date</label>
                    <div><input type="text" name="data[date]" value={this.state.date} onChange={this.handleDateChange} className="form-control terms-date" /></div>
                  </div>
                </div>
                <br style={{clear: 'both'}} />

                <Summary name="Full Summary" section={'fullSummary'} data={this.state.data.fullSummary} updateformData={this.updateformData}/>
                <Summary name="Change Summary" section={'changeSummary'}data={this.state.data.changeSummary} updateformData={this.updateformData}/>

                <div className="term-section">
                  <div className="form-controls">
                    <div className="terms-left">
                      <button id="terms-save" onClick={this.save} className="btnSubmit btn btn-primary">Save</button>
                    </div>
                    <div>
                      <button id="terms-cancel" onClick={this.success} className="btn btn-default">Cancel</button>
                    </div>
                  </div>
                </div>
              </form>
            </div>
          </div>
        </div>
      );
    }
  });

  return EditableTerms;
});