var Quiz = {

  /* Handles returns within the create-question form */
  captureKeypress: function(evt) {
    var keyCode = evt.keyCode ? evt.keyCode :
      evt.charCode ? evt.charCode : evt.which;
    if (keyCode == Event.KEY_RETURN) {
      if(Event.element(evt).id=='question_question')
        $('question_answer').focus();
      if(Event.element(evt).id=='question_answer')
        $('new_question').onsubmit();
      return false;
    }
    return true;
  },
  
  /* Hides and shows help messages while editing a quiz */
  updateHints: function() {
    $('quiz').cleanWhitespace();
    if($A($('quiz').childNodes).any()) {
      $('done').show();
      $('starting').hide();
    }
  },

  /* Reveals the answer node for a question */
  reveal: function(questionId) {
    $(questionId+'_a').visualEffect('blind_down', {duration:0.25})
  },

  /* Handles submitting an answer */
  answer: function(quizId, questionId, right) {
    var url = '/quizzes/' + quizId + ';answer';
    var params = 'question_id=' + questionId +
                 '&right='      + (right ? 'true' : false) +
                 '&last='       + this.questions().last().id;
    new Ajax.Request(url, {parameters:params});
    $(questionId.toString()).visualEffect('fade_up', {duration:0.5});
    if(this.showingQuestions() && !$('finished').visible())
      $('finished').visualEffect('appear_down');
    $('startover').show();
  },

  /* Returns all question DOM nodes */
  questions: function() {
    var questions = $('questions');
    questions.cleanWhitespace();
    return $A(questions.childNodes);
  },
  
  /* Returns whether there are any showing question nodes */
  showingQuestions: function() {
    return this.questions().select(function(e){
      return e.visible();
    }).length==1;
  }

}

// Custom effect combining BlindUp and Fade
Effect.FadeUp = function(element) {
  element = $(element);
  element.makeClipping();
  return new Effect.Parallel(
    [ new Effect.Opacity(element, {from:1,to:0}),
      new Effect.Scale(element, 0, 
        {scaleX:false,scaleContent:false,restoreAfterFinish: true}) ],
    Object.extend({
      to: 1.0,
      from: 0.0,
      transition: Effect.Transitions.linear,
      afterFinishInternal: function(effect) { 
        effect.effects[0].element.hide();
        effect.effects[0].element.undoClipping();
      }}, arguments[1] || {})
  );
}


// Custom effect combining BlindDown and Appear
Effect.AppearDown = function(element) {
  element = $(element);
  var elementDimensions = element.getDimensions();
  return new Effect.Parallel(
    [ new Effect.Opacity(element, {from:0,to:1}),
      new Effect.Scale(element, 100, 
        {from:0,to:1,scaleX:false,scaleContent:false,restoreAfterFinish:true,
         scaleMode:{originalHeight:elementDimensions.height,
           originalWidth:elementDimensions.width}}) ],
    Object.extend({
      transition: Effect.Transitions.linear,
      afterSetup: function(effect) {
        effect.effects[0].element.makeClipping();
        effect.effects[0].element.setStyle({height: '0px'});
        effect.effects[0].element.show(); 
      },  
      afterFinishInternal: function(effect) { 
        effect.effects[0].element.undoClipping();
      }}, arguments[1] || {})
  );
}
